
import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;

/**
Focus of this class is to define all types of account transactions which update and handle
transactions involving user accounts data file. The methods in this class will not include
transactions that update tickets data file

@author Jude Antonyrajan, Matt Chan, Zehan Song
@version 1.0
@since  2019-03-05                                                            
*/

class AccountTransaction{

	
   /**
   * This method updates/increases credits of the user by the value specified
   * @param data 	   First param which is the transaction data as a string
   * @param usersData  Second param containing all users data from user accounts file
   * 					as a string ArrayList
   * @return 		   nothing (void)
   */
   
    public static void updateAddCredit(String data, ArrayList<String> usersData) {

    	String username = data.substring(3, 18);

    	//the code below gets the user's data string, finds the portion which contains credits
    	// and then converts it to float
    	int userDataIndex = BackEnd.findUser(username, usersData);
    	String userData = usersData.get(userDataIndex);  // using index

    	float creditsToAdd = Float.parseFloat(data.substring(22,31));
		System.out.println(creditsToAdd);

    	float availableCredits = Float.parseFloat(userData.substring(19, 28));
    	float newTotalCredits = availableCredits + creditsToAdd;
    	String newUserData = userData.substring(0,19) + BackEnd.floatToStringFormat(newTotalCredits, 9);

    	usersData.set(userDataIndex, newUserData);
    	System.out.println(usersData.toString());
    }
    
    /**
     * This method increases credits of the buyer and reduces credits of the seller by
     * the same amount specified
     * @param data 	   		First param which is the transaction data as a string
     * @param usersData  	Second param containing all users data from user accounts file
     * 						as a string ArrayList
     * @return 				nothing (void)
     */
    
    public static void updateRefund(String data, ArrayList<String> usersData) {

    }


    
   /**
   * This method creates a new user with the information provided in the log, and
   * appends to the user accounts array list
   * @param data 	   First param which is the transaction data as a string
   * @param usersData  Second param containing all users data from user accounts file
   * 				   as a string ArrayList
   * @return 		   nothing (void)
   */
    
    public static void updateCreate(String data, ArrayList<String> usersData) {
    	usersData.add(data.substring(3, 31));
    	System.out.println(usersData.toString());

    }


}