import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;


/*
Focus of this class is to define all types of account transactions which update and handle
transactions involving user accounts data file AND tickets file. The methods in this class 
will include transactions that update tickets data file as well as users account file.

@author Jude Antonyrajan, Matt Chan, Zehan Song, 
@version 1.0
@since  2019-03-05                                                            
*/

class TicketTransaction{

   /**
   * In contrary to updateCreateUser(), this method deletes the specified user
   * from user accounts ArrayList and their relevant tickets from tickets ArrayList,
   * if its available.
   * 
   * @param data 	   	First param which is the create transaction data as a string
   * @param usersData  	Second param containing all users data from user accounts file
   * 					as a string ArrayList
   * @param ticketData  Third param containing all tickets data from tickets data file
   * 					as a string ArrayList
   * @return 			nothing (void)
   */
	
    public static void updateDelete(String data, ArrayList<String> usersData, ArrayList<String> ticketData) {
    	String username = data.substring(3, 18);
    	for (int i=0; i < ticketData.size(); i++) {
            // delete lines in tickets file with the username
            System.out.println(ticketData.get(i).substring(26,41));
    		if (ticketData.get(i).substring(26, 41).equals(username)) {
    			ticketData.remove(i);
    		}
    	}
		usersData.remove(BackEnd.findUser(username, usersData));
		System.out.println(ticketData.toString());
		System.out.println(usersData.toString());
    }

    /**
     * This method updates/adds new ticket for sale to the end of tickets data ArrayList
     * @param data  		First param which is the sell transaction data as a string
     * @param usersData     Second param containing all users data from user accounts file
     * 					    as a string ArrayList
     * @param ticketData 	Third param containing all tickets data from tickets data file
     * 					  	as a string ArrayList
     * @return 				nothing (void)
     */
    
    public static void updateSell(String data, ArrayList<String> ticketData){
        //Adds part of the sell transaction log to the end of tickets data
    	ticketData.add(data.substring(3, 55));
    }

    /**
     * This method reduces the tickets of a seller from tickets file as well as 
     * decreases calculated credits from buyer's data
     * @param data  	  First param which is the sell transaction data as a string
     * @param usersData   Second param containing all users data from user accounts file
     * 					  as a string ArrayList
     * @param ticketData  Third param containing all tickets data from tickets data file
     * 					  as a string ArrayList
     * @return 			  nothing (void)
     */
    
    public static void updateBuy(String data, ArrayList<String> usersData, ArrayList<String> ticketData) {
		
    	 //we will decrease credits from buyer in next phase

		 for (int i=0; i < ticketData.size(); i++) {
			 String tdata = ticketData.get(i);
			 //if a line in ticket data contains the event name
			 if (tdata.contains(data.substring(3, 28))) {
				 //then replace current ticket data with part of the buy trasanction log
				 //which holds the information to remaining tickets.
				 ticketData.set(i, data.substring(3,55));
			 }
		 }
    }

}