package protobba.server;
/**
 * junixsocket
 *
 * Copyright (c) 2009 NewsClub, Christian Kohlschütter
 *
 * The author licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import java.io.File;
import java.io.IOException;
import java.net.Socket;

import org.newsclub.net.unix.AFUNIXServerSocket;
import org.newsclub.net.unix.AFUNIXSocketAddress;

/**
 * Simple server, this guys accept incoming connection and give them to a handler
 * @author matdumsa
 *
 */
public class Server {
    public static void main(String[] args) throws IOException {
        final File socketFile = new File("/tmp/bba_server.sock");

        AFUNIXServerSocket server = AFUNIXServerSocket.newInstance();
        server.bind(new AFUNIXSocketAddress(socketFile));
        System.out.println("server: " + server);

        while (!Thread.interrupted()) {
            System.out.println("Waiting for connection...");
            Socket sock = server.accept();
            ServerSocketHandler handler = new ServerSocketHandler(sock);
            (new Thread(handler)).start();

        }
    }
}