#ifndef THREAD_H
#define	THREAD_H

#include <pthread.h>
#include <semaphore.h>
#include <set>

class Mutex {
public:
    Mutex();
    ~Mutex();
    void lock();
    bool trylock();
    void free();
private:
    pthread_mutex_t handle;
};

class Semaphore {
public:
    Semaphore(int = 0);
    ~Semaphore();
    void wait();
    bool trywait();
    void signal();
private:
    sem_t handle;
};

typedef pthread_t ThreadID;

class ThreadManager {
private:
    std::set<ThreadID> threads;
    Mutex threadsLock;

public:
    ThreadID create(void*(*)(void*), void* = 0);
    void exitThread();
    void join(ThreadID);
};

#endif	/* THREAD_H */

