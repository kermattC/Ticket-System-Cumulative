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

        String pad = "0";
        String username = data.substring(3, 18);

        //the code below gets the user's data string, finds the portion which contains credits
        // and then converts it to float
        int userDataIndex = BackEnd.findUserIndex(username, usersData);
        String userData = usersData.get(userDataIndex);  // using index

        float creditsToAdd = Float.parseFloat(data.substring(22,31));
        //System.out.println(creditsToAdd);

        float availableCredits = Float.parseFloat(userData.substring(19, 28));
        float newTotalCredits = availableCredits + creditsToAdd;
        String newCredits = String.format("%6.2f", newTotalCredits);
        newCredits = pad.repeat(9-newCredits.length()) + newCredits;
        String newUserData = userData.substring(0,19) + newCredits;

        usersData.set(userDataIndex, newUserData);
        // System.out.println(usersData.toString());
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

        String pad = "0";
        float credits = Float.parseFloat(data.substring(35,44));

        String buyerName = data.substring(03, 18);
        int buyerIndex = BackEnd.findUserIndex(buyerName, usersData);
        String buyerInfo = usersData.get(buyerIndex);

        float buyerCredits = Float.parseFloat(buyerInfo.substring(19,28));
        //add credits to buyer
        float newCreds = buyerCredits + credits;
        String newBuyerCredits = String.format("%6.2f", newCreds);
        newBuyerCredits = pad.repeat(9-newBuyerCredits.length()) + newBuyerCredits;
        buyerInfo = buyerInfo.substring(0, 19) + newBuyerCredits;
        usersData.set(buyerIndex, buyerInfo);

        System.out.println("UPDATED: " + buyerInfo);

        String sellerName = data.substring(19, 34);
        int sellerIndex = BackEnd.findUserIndex(sellerName, usersData);
        String sellerInfo = usersData.get(sellerIndex);
        float sellerCredits = Float.parseFloat(sellerInfo.substring(19,28));

        //deduct credits from seller
        newCreds = sellerCredits - credits;
        String newSellerCredits = String.format("%6.2f", newCreds);
        newSellerCredits = pad.repeat(9-newSellerCredits.length()) + newSellerCredits;
        sellerInfo = sellerInfo.substring(0,19) + newSellerCredits;
        usersData.set(sellerIndex, sellerInfo);
        System.out.println("UPDATED: " + sellerInfo);
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
        // System.out.println(usersData.toString());

    }
}