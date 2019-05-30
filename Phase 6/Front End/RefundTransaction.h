#pragma once

#include <string>
#include "Account.h"
#include "Transaction.h"

using namespace std;

/**
* RefundTransaction
* A RefundTransaction is used for the refund transaction
*
* @author Stephanie Phung
* @author Matt Chan
* @version 2.0
*/

class RefundTransaction : public Transaction {
    string current_user_accounts_file_;
    string buyer_username_;
    string seller_username_;
    double credit_;

  	/**
  	* Saves transaction data to output file, following the format X_U_S_C, where
  	* the values represent transaction code, buyer's username, seller's username,
    * and credit to refund, respectively.
  	*
  	* @param transaction_code unique transaction code identifier.
  	* @param file_name name of the output file.
  	* @param account account details to save.
  	*/
    void SaveToOutput(int transaction_code, string file_name, Account* account);


    /**
    * Checks that a username is valid and meets all the constraints.
    *
    * @param username username to verify.
    * @return bool true if valid.
    */
    bool ValidUsername(string username);

    /**
    * Runs the program logic for a refund.
    *
    * @param buyer_username name of buyer to refund to
    * @param seller_username name of seller to take credits from
    * @param credit amount to refund
    */
    void AttemptRefund(string buyer_username, string seller_username, double credit);

    public:
        const int kRefundTransactionCode = 5;

      	/**
      	* Initializes a RefundTransaction for an account, and saves the name
      	* of the current user accounts file for later use.
      	*
      	* @param current_user account that wants to do a transaction.
      	* @param current_user_accounts_file name of the user accounts file.
      	*/
        RefundTransaction(Account current_user, string current_user_accounts_file);

      	/**
      	* Executes the program logic for the RefundTransaction
      	*
      	* @param transaction_code unique transaction code identifier.
      	* @return Account updated details after transaction is executed.
      	*/
        Account Execute(int transaction_code);
};
