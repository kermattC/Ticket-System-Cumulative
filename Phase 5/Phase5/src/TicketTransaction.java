import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;

// interesting parts
// why you chose your front end
// (2 if statements, loop in separate spots)
// make each branch have different assignments of different variables 

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
            //System.out.println(ticketData.get(i).substring(26,41));
            if (ticketData.get(i).substring(26, 41).equals(username)) {
                ticketData.remove(i);
            }
        }
        if (BackEnd.findUserIndex(username, usersData) != -1)
            usersData.remove(BackEnd.findUserIndex(username, usersData));
        // System.out.println(ticketData.toString());
        // System.out.println(usersData.toString());
    }

    /**
     * This method updates/adds new ticket for sale to the end of tickets data ArrayList
     * @param data  		First param which is the sell transaction data as a string
     * @param ticketData 	Second param containing all tickets data from tickets data file
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

    public static void updateBuy(String data, ArrayList<String> usersData, ArrayList<String> ticketData, ArrayList<String> transactionData) {
        int line = 0;
        String pad = "0";
        Boolean exists = false;

        for (int i = 0; i < ticketData.size(); i++){
            String tData = ticketData.get(i);
            // System.out.println(tData);
            // check that ticket exists
            if (data.substring(3,28).equals(tData.substring(0,25))){
                line = i;
                exists = true;
            }
        }

        if (exists){
            // retrieve info from data arraylist
            String sellerName = data.substring(29,44);

            // retrieve ticket info
            String ticketInfo = ticketData.get(line);
            double ticketCurrent = Double.parseDouble(ticketInfo.substring(42,45));

            // calculate total cost of transaction
            double numOfTickets = Double.parseDouble(data.substring(45,48));
            double costPer = Double.parseDouble(data.substring(49,55));
            double totalCost = (ticketCurrent - numOfTickets) * costPer;
            // System.out.println(totalCost);


            // UPDATE TICKET COUNT

            // convert ticket amount back to string and padd 0's
            // String newTickets = Float.toString(numOfTickets);
            String newTickets = String.format("%1.0f", numOfTickets);
            newTickets = pad.repeat(3- newTickets.length()) + newTickets;
            // replace new ticket amount
            ticketInfo = ticketInfo.substring(0, 42) + newTickets + " " + ticketInfo.substring(46,52);
            ticketData.set(line, ticketInfo);

            // UPDATE SELLER'S BALANCE
            // retrieve seller info
            int sellerIndex = BackEnd.findUserIndex(sellerName, usersData);
            String sellerInfo = usersData.get(sellerIndex);
            double sellerCredits = Double.parseDouble(sellerInfo.substring(19,28));

            // calculate the seller's new balance
            String newSellerCredits = String.format("%6.2f", sellerCredits += totalCost);
            newSellerCredits = pad.repeat(9-newSellerCredits.length()) + newSellerCredits;
            // update the seller
            sellerInfo = sellerInfo.substring(0, 19) + newSellerCredits;
            usersData.set(sellerIndex, sellerInfo);

            // UPDATE BUYER'S BALANCE
            // extra step of finding the buyer's name
            // locate buyer's name in the next logout transaction
            // start by finding the index
            int startIndex = transactionData.indexOf(data);
            String buyerName = BackEnd.findBuyer(transactionData, startIndex);
            // find buyer details and reduce the credits
            int buyerIndex = BackEnd.findUserIndex(buyerName, usersData);
            String buyerInfo = usersData.get(buyerIndex);
            System.out.println(buyerInfo);
            double buyerCredits = Double.parseDouble(buyerInfo.substring(19,28));
            System.out.println(buyerCredits);
            // finalize the credits
            String newBuyerCredits = String.format("%6.2f", buyerCredits -= totalCost);
            newBuyerCredits = pad.repeat(9-newBuyerCredits.length()) + newBuyerCredits;
            // update the buyer
            buyerInfo = buyerInfo.substring(0, 19) + newBuyerCredits;
            usersData.set(buyerIndex, buyerInfo);

            System.out.println("UPDATED: " + ticketData.get(line));
            System.out.println("UPDATED: " + usersData.get(sellerIndex));
            System.out.println("UPDATED: " + usersData.get(buyerIndex));

        }else{
            System.out.println("ERROR - Ticket: " + data.substring(3,28) + " not found");
        }
    }
}