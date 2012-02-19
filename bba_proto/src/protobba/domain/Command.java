package protobba.domain;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import protobba.server.BlackBoard;
import protobba.server.ServerSocketHandler;

/**
 * An abstract command, to be exchanged between the BBM and the participants (KS and CS)
 * @author matdumsa
 *
 */
public abstract class Command {

	public static String split = "ô";
	
	public abstract boolean execute(BlackBoard blackboard, ServerSocketHandler handler);
	
	public abstract String getParametersSerialized();
	public abstract String getCommandName();
	
	public void sendToBlackboard(InputStream is, OutputStream os) throws IOException, ServerException {
		String serializedCommand = getCommandName() + split + getParametersSerialized();

		System.out.print(serializedCommand);
		os.write(serializedCommand.getBytes());
        os.flush();

		byte[] buf = new byte[128];
		int read = is.read(buf);

		if (read == -1) {
			throw new IOException("Connection with the server was interrupted");
		}
		else {
			String response = new String(buf, 0, read);
			System.out.println(":"+response);
			if (response.startsWith(("ok")) == false)
				throw new ServerException ("Server replied something else than ok, " + response);

			
		}
	}
}
