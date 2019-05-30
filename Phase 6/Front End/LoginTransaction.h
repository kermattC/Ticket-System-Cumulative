#pragma once

#include "Transaction.h"

/**
* LoginTransaction
* LoginTransaction is a unique transaction and has its
* own class. It manages all the program logic for logging in,
* including reading in from a current user accounts file.
*
* @author Stephanie Phung
* @author Matt Chan
* @version 2.0
*/
class LoginTransaction : public Transaction {
	string current_user_accounts_file_;

	/**
	* Outputs an error message unique to this class.
	*/
	void ErrorMessage();

	/**
	* Runs through the program logic to determine
	* if a username is valid.
	*
	* @param username username to log in with.
	* @return bool true if login is successful.
	*/
	bool LoginSuccessful(string username);

	/**
	* Reads a line of data and returns the username.
	* This function should be used when reading in data
	* from the current user accounts file.
	*
	* @param line line of data to read from file.
	* @return string username read from the line.
	*/
	string ParseUsername(string line);

	/**
	* A placeholder function in case we ever need to keep record of login transactions.
	*
	* @param transaction_code the unique transaction code identifier.
	* @param file_name the name of the file.
	* @param account account details to save.
	*/
	void SaveToOutput(int transaction_code, string file_name, Account* account);
public:
	const int kLoginTransactionCode = -1;

	/**
	* Initializes a LoginTransaction and saves the name of the current
	* user accounts file.
	*
	* @param current_user_accounts_file name of the user accounts file.
	*/
	LoginTransaction(string current_user_accounts_file);

	/**
	* Executes the program logic for logging in. The transactio code is currently
	* only necessary to override the parent method, but will be useful if we decide
	* to implement SaveToOutput(int, string).
	*
	* @param transaction_code unique transaction code identifier.
	* @return Account modified details from the transaction.
	*/
	Account Execute(int transaction_code);
};
