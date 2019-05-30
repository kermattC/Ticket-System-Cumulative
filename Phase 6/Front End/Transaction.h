#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> // stringstream
#include <iomanip> // set precision
#include "Account.h"

using namespace std;

/**
* Transaction
* This is a virtual class designed to keep all transactions
* organized. It contains information on the different types of
* data you can use to execute any transaction. It also contains
* useful functions to support its subclasses.
*
* @author Stephanie Phung
* @author Matt Chan
* @version 2.0
*/

class Transaction {
protected:
	const int kTransactionCodeLength = 2;
	const int kUsernameLength = 15;
	const int kAccountTypeLength = 2;
	const int kCreditsLength = 9;
	const int kEventNameLength = 25;
	const int kPriceLength = 6;
	const int kTicketsLength = 3;
	const string kKeyTransactionCode = "X";
	const string kKeyUsername = "U";
	const string kKeyAccount = "A";
	const string kKeyCredits = "C";
	const string kKeyEventName = "E";
	const string kKeySellerName = "S";
	const string kKeyNumberOfTickets = "T";
	const string kKeyTicketPrice = "P";
	const string kOutputFileName = "transaction_stream.output";
	const string kDeletedUserFileName = "deleted_users.data";
	const string kKeyEnd = "END";
	const int kEndLength = kKeyEnd.length();

	int transaction_code_;
	Account account_;

	/**
	* Outputs a generic error message for invalid input.
	*/
	void ErrorMessage();

	/**
	*	Checks to see if a username is deleted.
	*
	* @param username username to check
	* @return bool true if deleted
	*/
	bool IsDeleted(string username);

	/**
	* Converts a word to uppercase.
	*
	* @param word word to convert.
	* @return string of converted word.
	*/
	string ToUpper(string word);

	/**
	* Converts a double into a string with two decimal places.
	*
	* @param credit value of credits to convert.
	* @return string string representation of total credits.
	*/
	string CreditToString(double credit);

	/**
	* Returns the string value padded appropriately by the type
	* of data it is. This is used for formatting data before
	* saving to output.
	*
	* @param data_type identifier for type of data.
	* @param value value of data in string.
	* @return string returns the padded value.
	*/
	string Padd_Spaces(string data_type, string value);
public:
	/**
	* Executes the program logic for the type of transaction based on the
	* type of transaction it is.
	*
	* @param transaction_code the unique identifier of each transaction.
	* @return Account the modified account after transaction has been made.
	*/
	virtual Account Execute(int transaction_code) = 0;

	/**
	* Saves the transaction information to the output file.
	*
	* @param transaction_code the unique identifier of each different type of transaction.
	* @param file_name the name of the file to save to.
	* @param account the account details to save.
	*/
	virtual void SaveToOutput(int transaction_code, string file_name, Account* account) = 0;

	/**
	* Parses the line of data in the user accounts file based on data type.
	* Used to find the username, account type, and credits of a user.
	*
	* @param data_type type of data to find (in this case either username, type, or credits).
	* @param line line in the file to parse.
	* @return string returns the value of the data.
	*/
	string ParseAccountData(string data_type, string line);

	/**
	* Reads in an entire line from the current account file.
	*
	* @param file_name name of current user accounts file.
	* @param username name of user to get information of.
	* @return string returns entire line from the accounts file.
	*/
	string GetAccountDetails(string file_name, string username);
};
