import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;

public class BackEnd{
    private static final String TICKETS_FILE = "available_tickets.data";
    private static final String USERS_FILE = "current_user_accounts.data";
    private static final String TRANSACTION_FILE = "daily_transactions.data";
    private static ArrayList<String> ticketData, usersData, transactionData;


    /**
     * This is the main method which makes use of update transaction methods and writes
     * new files containing all updated information/data after running daily transaction data.
     * @author Jude Antonyrajan, Matt Chan, Zehan Song
     * @param 	args Unused.
     * @return 	Nothing (void).
     */

    public static void main(String[] args){
        ticketData = getTicketData();
        usersData = getUsersData();
        transactionData = getTransactionData();

    	for (String data : transactionData) {
    		System.out.println(data.substring(0,2));
    		if (data.substring(0,2).equals("03")) {
    			TicketTransaction.updateSell(data, ticketData);
    		}
    		else if (data.substring(0,2).equals("04")) {
    			TicketTransaction.updateBuy(data, usersData, ticketData);
        }
        else if (data.substring(0,2).equals("02")) {
    			TicketTransaction.updateDelete(data, usersData, ticketData);
    		}
        else if (data.substring(0,2).equals("01")) {
    	    AccountTransaction.updateCreate(data, usersData);
    		}

    		else if (data.substring(0,2).equals("06")) {
          AccountTransaction.updateAddCredit(data, usersData);
    		}

    		else if (data.substring(0,2).equals("05")) {

    		}
        }
        saveToOutput(usersData, ticketData);
    }


    /**
     * This method is used to retrieve data from Tickets data file and store them
     * into Tickets data ArrayList.
     * @return ArrayList<String> This returns the filled string
     * 							 ArrayList of Tickets file data.
     */


    public static ArrayList<String> getTicketData(){
        try{
            File ticketsFile = new File(TICKETS_FILE);
            BufferedReader ticketBr = new BufferedReader(new FileReader(ticketsFile));
            String ticketString;
            // store into ticket arraylist
            ArrayList<String> ticketData = new ArrayList<String>();
            while((ticketString = ticketBr.readLine()) != null){
                ticketData.add(ticketString);
            }
            ticketBr.close();
             return ticketData;
        }catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }

    /**
     * This method is used to retrieve data from Users data file and store them
     * into Users data ArrayList.
     * @return ArrayList<String> This returns the filled string
     * 							 ArrayList of Users file data.
     */

    public static ArrayList<String> getUsersData(){
        try{
            File ticketsFile = new File(USERS_FILE);
            BufferedReader userBr = new BufferedReader(new FileReader(ticketsFile));
            String userString;
            // store into users arraylist
            ArrayList<String> userData = new ArrayList<String>();
            while((userString = userBr.readLine()) != null){
                userData.add(userString);
            }
            userBr.close();
             return userData;
        }catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }

    /**
     * This method is used to retrieve data from Transactions data file and store them
     * into Transactions data ArrayList.
     * @return ArrayList<String> This returns the filled string
     * 							 ArrayList of Transactions file data.
     */

    public static ArrayList<String> getTransactionData(){
        try{
            File transactionFile = new File(TRANSACTION_FILE);
            BufferedReader transactionBr = new BufferedReader(new FileReader(transactionFile));
            String transactionString;
            // store into transaction arraylist
            ArrayList<String> transactionData = new ArrayList<String>();
            while((transactionString = transactionBr.readLine()) != null){
                transactionData.add(transactionString);
            }
            transactionBr.close();
             return transactionData;
        }catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }

    /**
     * This method converts float value to string and adds trailing zeros
     * to the front to meet necessary transaction log format. i.e (000105.00)
     * @param f 			First param which is the float that needs to be converted to string
     * @param constraint 	Int value indicating number of allocated characters in log format
     * @return String 		Zeros concatenated with string format of float value
     */

    public static String floatToStringFormat(float f, int constraint) {
    	String formattedString = String.format("%.02f", f), pattern = "";

    	for (int i=0; i<constraint-formattedString.length(); i++) {
    		pattern += '0';
    	}
    	return pattern + formattedString;
    }

    /**
     * This method finds the targeted user from Users account array list
     * and returns the index of their data string.
     * @param target 	First param, username of the individual required to search (string)
     * @param usersData Second param containing all users data from user accounts file
     * 		  			as a string ArrayList
     * @return int 		index of the user's data string in user accounts ArrayList
     */

    public static int findUser(String target, ArrayList<String> usersData){
        for (int i = 0; i < usersData.size(); i++){
            String line = usersData.get(i);
            if (line.substring(0,15).equals(target)){
            	return i;
            }
        }
		return -1;
    }

    /**
     * This method creates/updates new user accounts and ticket files with updated
     * information after running daily transaction logs.
     * @param usersData 	First param containing all users data from user accounts file
     * 		  		    	as a string ArrayList.
     * @param ticketData 	Second param containing all ticket and event data from tickets file
     * 		             	as a string ArrayList.
     * @return 				none (void).
     */

    public static void saveToOutput(ArrayList<String> usersData, ArrayList<String> ticketData){
        try{
            PrintWriter aWriter = new PrintWriter("new_user_accounts.data", "UTF-8");
            for (int i = 0; i < usersData.size(); i++){
                aWriter.println(usersData.get(i));
            }
            PrintWriter tWriter = new PrintWriter("new_ticket_file.data", "UTF-8");
            for (int i = 0; i < ticketData.size(); i++){
                tWriter.println(ticketData.get(i));
            }
        aWriter.close();
        tWriter.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}