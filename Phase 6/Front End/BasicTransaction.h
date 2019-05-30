#pragma once

#include "Transaction.h"

/**
* BasicTransaction
* A BasicTransaction is used for the following four transactions:
* create, delete, add credit, and end session (logout).
*
* @author Stephanie Phung
* @author Matt Chan
* @version 2.0
*/
class BasicTransaction : public Transaction {
	string current_user_accounts_file_;
	string username_;
	string account_type_;
	double credit_;

	/**
	* Save the transaction details in the format X_U_T_C where variables
	* represent transaction code, username, account type, and amount of
	* credits, respectively, to a file.
	*
	* @param transaction_code unique transaction code to identify the type of transaction.
	* @param file_name the name of the file to save to.
	* @param account account details to save.
	*/
	void SaveToOutput(int transaction_code, string file_name, Account* account);

	/**
	 *  Returns a boolean to check if the inputted data is valid,
	 *  checks if the username, account type and credits are within
	 *  character limits.
	 *
	 * @param the new username of the account
	 * @param the new account type of the account
	 * @param amount of credits to be put into the account
	 * @return bool returns true if all inputs satisfy all conditions
	 */
	bool IsValidCreate(string username, string account_type, double credit);

	/**
	 *  Returns a boolean to check if the inputted data is valid,
	 *  checks if the username is within the character limit when
	 *  the user inputs it
	 *
	 * @param username of the account to be deleted
	 * @return bool returns true if the username satisfy all conditions
	 */
	bool IsValidDelete(string username);

	/**
	 * Outputs the username of the deleted account to the
	 * deled_users.data file after doing a series of checks to
	 * make sure that the user is valid to be deleted. Also outputs
	 * the transaction details to the daily_transaction
	 *
	 * @param username of the account to be deleted
	 */
	void Delete(Account* account);

	/**
	 * Outputs the transaction details to the transaction_stream.output
	 * file after doing a series of checks to make sure that the new account
	 * information is valid.
	 *
	 * @param username of the new account
	 * @param the account type of the new account
	 * @param amount of credits to be put into the new account
	 */
	void Create(string new_account_name, string new_account_type, double new_account_credit);

	/**
	 * Used to compare the inputted username with the file contents
	 *
	 * @param username of the new account
	 * @param the account type of the new account
	 * @param amount of credits to be put into the new account
	 */
	bool Compare(string line, string del_account_name);

	/**
	* Adds amount of credit to account if all inforation is valid.
	*
	* @param account account to add credits to
	* @param amount total of credits to add
	*/
	void AddCreditsAndSave(Account* account, double amount);
public:
	const int kCreateTransactionCode = 1;
	const int kDeleteTransactionCode = 2;
	const int kAddCreditTransactionCode = 6;
	const int kEndSessionTransactionCode = 0;

	const double kMaxCreditToAdd = 1000.00;

	/**
	* Prepares a BasicTransaction for an account.
	*
	* @param account the account that wants to do a transaction.
	*/
	BasicTransaction(Account account, string current_user_accounts_file);

	/**
	* Executes the program logic for BasicTransaction,
	* identified by a unique transaction code.
	*
	* @param transaction_code the unique transaction code.
	* @return Account the updated account details after the transaction.
	*/
	Account Execute(int transaction_code);
};
