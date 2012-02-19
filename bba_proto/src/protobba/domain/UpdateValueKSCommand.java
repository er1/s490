package protobba.domain;

import protobba.server.BlackBoard;
import protobba.server.ServerSocketHandler;

public class UpdateValueKSCommand extends Command {
	
	private String itemName;
	private int value;
	
	public UpdateValueKSCommand(String itemName, int value) {
		this.itemName = itemName;
		this.value = value;
	}
	
	public static String commandName() {
		return "UpdateValue";
	}
	
	public String getItemName() {
		return itemName;
	}

	public static UpdateValueKSCommand fromString(String input) {
		String[] arr = input.split(Command.split);
		return new UpdateValueKSCommand(arr[1], Integer.parseInt(arr[2]));
	}
	
	@Override
	public boolean execute(BlackBoard blackboard, ServerSocketHandler handler) {
		return blackboard.updateValue(handler.getConnectionId(), itemName, value);
	}

	@Override
	public String getParametersSerialized() {
		return getItemName() + Command.split + value;		
	}

	@Override
	public String getCommandName() {
		return commandName();
	}

}
