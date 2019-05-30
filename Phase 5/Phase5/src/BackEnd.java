import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;

public class BackEnd{
    private static final String TICKETS_FILE = "available_tickets.data";
    private static final String USERS_FILE = "current_user_accounts.data";
    private static final String TRANSACTION_FILE = "daily_transactions.data";
    private static ArrayList<String> ticketData, usersData, transactionData;
    private static final int CREDITS_LENGTH_LEFT = 6;
    private static final int CREDITS_LENGTH_RIGHT = 2;
    private static final int TICKETS_LENGTH = 3;
    private static final String KEY_CREDITS = "C";
    private static final String KEY_NUM_TICKETS = "T";


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

        String transactionCode = "";
        for (String data : transactionData) {
            transactionCode = data.substring(0,2);
            switch(transactionCode){
                case "03":
                    TicketTransaction.updateSell(data, ticketData);
                    break;
                case "04":
                    TicketTransaction.updateBuy(data, usersData, ticketData, transactionData);
                    break;
                case "02":
                    TicketTransaction.updateDelete(data, usersData, ticketData);
                    break;
                case "01":
                    AccountTransaction.updateCreate(data, usersData);
                    break;
                case "06":
                   AccountTransaction.updateAddCredit(data, usersData);
                    break;
                case "05":
                    AccountTransaction.updateRefund(data, usersData);
                    break;
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
            System.out.println("File Not Found!");
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
            File usersFile = new File(USERS_FILE);
            BufferedReader userBr = new BufferedReader(new FileReader(usersFile));
            String userString;
            // store into users arraylist
            ArrayList<String> userData = new ArrayList<String>();
            while((userString = userBr.readLine()) != null){
                userData.add(userString);
            }
            userBr.close();
            return userData;
        }catch (IOException e){
            System.out.println("File Not Found!");
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
            System.out.println("File Not Found!");
        }
        return null;
    }

    /**
     * This method finds the targeted user from Users account array list
     * and returns the index of their data string.
     * @param target 	First param, username of the individual required to search (string)
     * @return int 		index of the user's data string in user accounts ArrayList
     */

    public static int findUserIndex(String target, ArrayList<String> data){
        for (int i = 0; i < data.size(); i++){
            String line = data.get(i);
            if (line.substring(0,15).equals(target)){
                return i;
            }
        }
        return -1;
    }

    /**
     * This method finds the targeted buyer from Users account array list
     * and returns the index of their data string. Specific to when updating the buyer's balance
     * @param data 	First param, arraylist containing user information
     * @param startIndex The line where the ticket transaction has been found. This is used as a starting
     *                  point when searching the users account info.
     * @return String 	returns the buyer's username
     */

    public static String findBuyer(ArrayList<String> data, int startIndex){
        for (int i = startIndex; i < data.size(); i++){
            String line = data.get(i);
            if (line.substring(0,2).equals("00")){
                return line.substring(3,18);
            }
        }
        return null;
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