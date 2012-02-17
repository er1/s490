package protobba.client;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import org.newsclub.net.unix.AFUNIXSocket;
import org.newsclub.net.unix.AFUNIXSocketAddress;
import org.newsclub.net.unix.AFUNIXSocketException;

import protobba.domain.RegisterKSCommand;
import protobba.domain.ServerException;
import protobba.domain.UpdateValueKSCommand;

/**
 * AbstractKS, this has the necessary components to reach the BB Manager, do the set-up for an item and update it
 * @author matdumsa
 *
 */
public class AbstractKS {

	private InputStream is = null;
	private OutputStream os = null;
	private AFUNIXSocket sock;
	private String item;
	
	public AbstractKS(String item) {
		this.item = item;
		initializeSocket(500, false);
	}
	
	private void initializeSocket(int delayBetweenRetries, boolean incrementDelay) {
		while (initializeSocket() == false) {
			try {
				Thread.sleep(delayBetweenRetries);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			if (incrementDelay)
				delayBetweenRetries = delayBetweenRetries*2;
			System.out.println("Was not able to connect to socket successfully, will retry in " + delayBetweenRetries);
		}
	}
	
	private boolean initializeSocket() {
		try {
			final File socketFile = new File("/tmp/bba_server.sock");

			AFUNIXSocket sock = AFUNIXSocket.newInstance();
			sock.connect(new AFUNIXSocketAddress(socketFile));
			System.out.println("Connected");

			is = sock.getInputStream();
			os = sock.getOutputStream();
			registerAsWriter();
			return true;
		} catch (AFUNIXSocketException e) {
			System.out.println("Cannot connect to server. Have you started it?");
		}
		catch (IOException e) {
		}
		return false;
	}

	private void registerAsWriter() {
		RegisterKSCommand command = new RegisterKSCommand(item);
		// Issue command to register interest in an item called Time
		try {
			command.sendToBlackboard(is, os);			
		}
		catch (IOException e) {
			initializeSocket(500, false);
			registerAsWriter();
		}
		catch (ServerException e) {
			System.out.println("Oups.. it looks like the server doesn't know how to handle a registration command");
			terminate();
		}
	}

	public void updateValue(int value) throws ServerException {
		UpdateValueKSCommand command = new UpdateValueKSCommand(item, value);
		// Issue command to register interest in an item called Time
		try {
			command.sendToBlackboard(is, os);			
		}
		catch (IOException e) {
			initializeSocket(500, false);
			updateValue(value);
		}
	}

	public void terminate() {
		try {
			os.close();
			is.close();
			sock.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("End of communication");
	}

}
