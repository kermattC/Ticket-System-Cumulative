#pragma once

#include <string>

using namespace std;

#define ADMIN_CODE "AA"
#define FULL_STANDARD_CODE "FS"
#define SELL_STANDARD_CODE "SS"
#define BUY_STANDARD_CODE "BS"

/**
* Account
* This class stores the data for an Account, and offers
* methods to interact with it.
*
* @author Stephanie Phung
* @author Matt Chan
* @version 2.0
*/
class Account {
	string username_;
	string account_type_;
	int type_code_;
	double credit_;
public:
	/**
	* This is the default constructor.
	*/
	Account();

	/**
	* A constructor to create an Account object and initialize
	* its variables.
	*
	* @param username this is the username of the account
	* @param account_type this is the account type
	* @param credit amount of credits an account has
	*/
	Account(string username, string account_type, double credit);

	/**
	* Returns the Account's username.
	*
	* @return string name of account.
	*/
	string GetName();

	/**
	* Returns the Account type.
	*
	* @return string account type.
	*/
	string GetType();

	/**
	* Returns the amount of credits in the Account.
	*
	* @return double total credits of account.
	*/
	double GetCredit();

	/**
	* A setter for username.
	*
	* @param username new username of account.
	*/
	void SetName(string username);

	/**
	* A setter for account type.
	*
	* @param account_type account type.
	*/
	void SetType(string account_type);

	/**
	* Used to change credit amount.
	*
	* @param credit new credit total.
	*/
	void SetCredit(double credit);
};
