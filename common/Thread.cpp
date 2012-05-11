/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "common.h"
#include "Thread.h"

Mutex::Mutex() {
    pthread_mutex_init(&handle, 0);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&handle);
}

void Mutex::lock() {
    pthread_mutex_lock(&handle);
}

bool Mutex::trylock() {
    return pthread_mutex_trylock(&handle) == 0;
}

void Mutex::free() {
    pthread_mutex_unlock(&handle);
}

Semaphore::Semaphore(int val) {
    sem_init(&handle, 0, val);
}

Semaphore::~Semaphore() {
    sem_destroy(&handle);
}

void Semaphore::wait() {
    sem_wait(&handle);
}

bool Semaphore::trywait() {
    return sem_trywait(&handle) == 0;
}

void Semaphore::signal() {
    sem_post(&handle);
}

ThreadID ThreadManager::create(void*(*start_routine)(void*), void* arg) {
    ThreadID thread;

    // create a new ThreadManager and let it start running
    exitOnFail(pthread_create(&thread, NULL, start_routine, arg) != 0, "ThreadManager: pthread_create");
    exitOnFail(pthread_detach(thread) != 0, "ThreadManager: pthread_detach");

    // add this ThreadManager id to the list of active ThreadManagers
    threadsLock.lock();
    threads.insert(thread);
    threadsLock.free();

    return thread;
}

void ThreadManager::exitThread() {
    // get this ThreadManager id
    pthread_t thisThreadManager = pthread_self();

    // remove this ThreadManager id from the list of active ThreadManagers
    threadsLock.lock();
    std::set<pthread_t>::iterator it = threads.find(thisThreadManager);
    if (it != threads.end()) {
        threads.erase(it);
    }
    threadsLock.free();

    // kill off this ThreadManager
    pthread_exit(0);
}

void ThreadManager::join(ThreadID tid) {
    void* x; // use for return value and then discard it;
    pthread_join(tid, &x);
}
