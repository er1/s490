package protobba.server;

import protobba.domain.Command;
import protobba.domain.RegisterInterestInItem;
import protobba.domain.RegisterKSCommand;
import protobba.domain.UpdateValueKSCommand;

public class CommandFactory {

	public static Command getCommand(String input) {
		String[] arr = input.split(Command.split);
		
		if (arr[0].equals(RegisterKSCommand.commandName()))
				return RegisterKSCommand.fromString(input);
		if (arr[0].equals(UpdateValueKSCommand.commandName()))
			return UpdateValueKSCommand.fromString(input);
		if (arr[0].equals(RegisterInterestInItem.commandName()))
			return RegisterInterestInItem.fromString(input);

		return null;
	}
}
