package protobba.client;

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
import java.io.InputStream;
import java.io.OutputStream;

import org.newsclub.net.unix.AFUNIXSocket;
import org.newsclub.net.unix.AFUNIXSocketAddress;
import org.newsclub.net.unix.AFUNIXSocketException;

import protobba.domain.RegisterInterestInItem;
import protobba.domain.ServerException;


/**
 * Simple Control Shell, register itself to the BB as interested in a given item and received messages only for this item.
 * TODO: Abstract it like KS
 * @author matdumsa
 *
 */
public class SimpleCS {
	public static void main(String[] args) throws IOException {
		final File socketFile = new File("/tmp/bba_server.sock");

		AFUNIXSocket sock = AFUNIXSocket.newInstance();
		try {
			sock.connect(new AFUNIXSocketAddress(socketFile));
		} catch (AFUNIXSocketException e) {
			System.out
					.println("Cannot connect to server. Have you started it?");
			System.out.flush();
			throw e;
		}
		System.out.println("Connected");

		InputStream is = sock.getInputStream();
		OutputStream os = sock.getOutputStream();
		try {
			{
				RegisterInterestInItem command = new RegisterInterestInItem("CurrentTime");
				// Issue command to register interest in an item called Time
				command.sendToBlackboard(is, os);
			}
			while (true) {

				{

					byte[] buf = new byte[128];
					int read = is.read(buf);

					if (read == -1) {
						// The server shut his connection, maybe a problem occured on
						// his side.
						System.out.println("Connection with server lost. Leaving");
						System.out.println();
					}

					System.out.println(new String(buf, 0, read));
					
				}

			}
		} catch (ServerException e) {
			e.printStackTrace();
		} 
		
		os.close();
		is.close();

		sock.close();
		System.out.println("End of communication.");

	}
}