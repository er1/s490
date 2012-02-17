package protobba.server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import protobba.domain.Command;

/**
 * ServerSocketHandler (SSH) is fired up anytime a new client (CS/KS).
 * When a KS connects, it sits there waiting for incoming request.
 * When a CS connects and register interest in one or several items, the SSH sends news about the items when advised to do so by the BBM.
 * @author matdumsa
 *
 */
public class ServerSocketHandler implements Runnable {

	private Socket sock;
	
	//This counter is incremented every time a new connection is established
	private static Integer connectionCounter = 0;
	private int currentConnectionId;
	private boolean running = false;
	private static Map<Integer, ServerSocketHandler> socketHandlerStore = Collections.synchronizedMap(new HashMap<Integer, ServerSocketHandler>());
	private static BlackBoard bb = new BlackBoard();
	private InputStream is = null;
	private OutputStream os = null;

	public ServerSocketHandler(Socket socket) {
		this.sock = socket;
		this.running = false;
		synchronized(connectionCounter) {
			connectionCounter++;
			currentConnectionId = connectionCounter;
		}
		
		socketHandlerStore.put(connectionCounter, this);
		
	}

	@Override
	public void run() {
		running = true;
		System.out.println("Connection established with party " + currentConnectionId);

		try {

			is = sock.getInputStream();
			os = sock.getOutputStream();

			while (running) {

				//Listen to a command
				byte[] buf = new byte[128];
				int read = is.read(buf);
				
				if (read==-1) {
					//The client cut his connection to the server in an uncool fashion.
					running=false;
					break;
				}
				String commandStr = new String(buf, 0, read);

				Command command = CommandFactory.getCommand(commandStr);
				if (command == null) {
					//Oups.. unknown command, complaint
					os.write(("Unknown command, " + commandStr).toString().getBytes());
					os.flush();
				}
				else {
					String response = "ok" + Command.split + command.execute(bb, this);
					os.write(response.getBytes());
					os.flush();
				}
				

			}


		} catch (IOException e) {

		}
		finally {
			terminate();
			
		}

	}

	private void terminate() {
		try {
			os.close();
			is.close();
			sock.close();			
			socketHandlerStore.remove(currentConnectionId);
			bb.releaseAllInterest(this);
			System.out.println("lost connection with party " + currentConnectionId + " " + socketHandlerStore.size() + " connections remaining");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
	
	public String getConnectionId() {
		return Integer.toString(currentConnectionId);
	}

	public void notifyItemHasChanged(String item, int value) {
		try {
			os.write((item + " has changed to " + value).toString().getBytes());
			os.flush();
		} catch (IOException e) {
			terminate();
		}		
	}

}
