package protobba.domain;

import protobba.server.BlackBoard;
import protobba.server.ServerSocketHandler;

public class RegisterKSCommand extends Command {

	
	private String itemName;

	public RegisterKSCommand(String itemName) {
		this.itemName = itemName;
	}
	
	public static String commandName() {
		return "RegisterKS";
	}
	
	public String getItemName() {
		return itemName;
	}

	public static RegisterKSCommand fromString(String input) {
		String[] arr = input.split(Command.split);
		return new RegisterKSCommand(arr[1]);
	}
	

	@Override
	public boolean execute(BlackBoard blackboard, ServerSocketHandler handler) {
		return blackboard.registerForWriting(handler.getConnectionId(), getItemName());
	}

	@Override
	public String getParametersSerialized() {
		return getItemName();
	}

	@Override
	public String getCommandName() {
		return commandName();
	}

}
