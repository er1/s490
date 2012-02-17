package protobba.server;

import java.util.HashMap;
import java.util.HashSet;

/**
 * BlackBoard, is responsible for managing all the data items for the system.
 * TODO:Also responsible for archiving the data in the telemetry store and the persistent store with a sampling policy
 * @author matdumsa
 *
 */
public class BlackBoard {

	private HashMap<String, BlackBoardItem> store = new HashMap<String, BlackBoardItem>();

	//Itemname -> Interested Process
	private HashMap<String, HashSet<ServerSocketHandler>> interestStore = new HashMap<String, HashSet<ServerSocketHandler>>();

	public BlackBoard() {
		
	}

	/**
	 * Register this KS as the only writer for a given item.
	 * @param KnowledgeSourceId, unique id of knowledge source
	 * @param item, name of the item the KS wants to register to
	 * @return TRUE if the resource was free or non-existent, FALSE if the resource is already assigned to someone else.
	 */
	public boolean registerForWriting(String KnowledgeSourceId, String item) {
		if (store.containsKey(item)) {
			//The item is on the black board
			if (store.get(item).getWriter() == null) {
				//Nobody owns it
				store.get(item).setWriter(KnowledgeSourceId);
				return true;
			}
				//Someone owns it
				return false;
		} 
		else {
			//The item is NOT on the black board, initialize it
			BlackBoardItem newItem = new BlackBoardItem();
			newItem.setName(item);
			newItem.setWriter(KnowledgeSourceId);
			newItem.setValue(0);
			store.put(item, newItem);
			return true;
		}
	}
	
	public boolean updateValue(String KnowledgeSourceId, String item, int value) {
		if (store.containsKey(item) == false)
			return false;
		if (store.get(item).getWriter() == null)
			registerForWriting(KnowledgeSourceId, item);
		if (store.get(item).getWriter().equals(KnowledgeSourceId) == false)
			return false;
		store.get(item).setValue(value);
		
		if (interestStore.containsKey(item)) {
			// Some people are interested in this!
			for (ServerSocketHandler handler : interestStore.get(item)) {
				handler.notifyItemHasChanged(item, value);
			}
		}
		return true;
	}
	
	public int getValue(String item) {
		if (store.containsKey(item) == false)
			return 0;
		else
			return store.get(item).getValue();
	}

	/**
	 * Register the interest from a client in an item.
	 * @param connectionId
	 * @param itemName
	 * @return
	 */
	public boolean registerInterest(ServerSocketHandler connection, String itemName) {
		if (interestStore.containsKey(itemName) == false)
			interestStore.put(itemName, new HashSet<ServerSocketHandler>());
		interestStore.get(itemName).add(connection);
		
		return true;
	}
	
	public boolean releaseAllInterest(ServerSocketHandler connection) {
		for (HashSet<ServerSocketHandler> listeners : interestStore.values())
			listeners.remove(connection);
		for (BlackBoardItem item : store.values())
			if (item.getWriter() != null && item.getWriter().equals(connection.getConnectionId()))
				item.setWriter(null);
		return true;
	}
	
}
