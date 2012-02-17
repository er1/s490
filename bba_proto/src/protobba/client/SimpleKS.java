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

import java.io.IOException;

import protobba.domain.ServerException;


public class SimpleKS extends AbstractKS {

	public SimpleKS(String item) {
		super(item);
	}

	public static void main(String[] args) throws IOException {

		SimpleKS timeKS = new SimpleKS("local-time");

		while (true) {
			try {
				timeKS.updateValue(
						(int) System.currentTimeMillis());
				Thread.sleep(500);
			} catch (ServerException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}