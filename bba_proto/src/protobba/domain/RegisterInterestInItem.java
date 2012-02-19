package protobba.domain;

import protobba.server.BlackBoard;
import protobba.server.ServerSocketHandler;

public class RegisterInterestInItem extends Command {
	public static String commandName() { return "RegisterInterestInItem"; }
	
	private String itemName;

	public RegisterInterestInItem(String itemName) {
		this.itemName = itemName;
	}
	
	public String getCommandName() {
		return commandName();
	}
	
	public String getItemName() {
		return itemName;
	}

	public static RegisterInterestInItem fromString(String input) {
		String[] arr = input.split(Command.split);
		return new RegisterInterestInItem(arr[1]);
	}
	
	public String getParametersSerialized() {
		return getItemName();
	}

	@Override
	public boolean execute(BlackBoard blackboard, ServerSocketHandler handler) {
		return blackboard.registerInterest(handler, getItemName());
	}

}
