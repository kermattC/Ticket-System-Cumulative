#pragma once

#include "Transaction.h"

/**
* Transaction
* A TicketTransaction is used for buying and selling,
* and is designed to interact with the tickets file.
*
* @author Stephanie Phung
* @author Matt Chan
* @version 2.0
*/
class TicketTransaction : public Transaction {
	string tickets_file_;

	string event_title_;
	double ticket_price_;
	int num_tickets_;
	string seller_username_;

	/**
	* Saves transaction data to output file, following the format X_E_S_T_P, where
	* the values represent transaction code, event title, seller's username, number
	* of tickets, and price per ticket respectively.
	*
	* @param transaction_code unique transaction code identifier.
	* @param file_name name of the output file.
	* @param account account details to save.
	*/
	void SaveToOutput(int transaction_code, string file_name, Account* account);

	/**
	* Parses the line of data in the tickets file based on data type.
	* Used to find the event title name and the seller's username.
	*
	* @param data_type type of data to find (in this case either title or username).
	* @param line line in the file to parse.
	* @return string returns either the event title or the username.
	*/
	string ParseData(string data_type, string line);

	/**
	* Saves the ticket data to the current TicketTransaction if it's valid.
	* This function must be successful before saving to output.
	*
	* @param line line of data to check from file.
	* @param num_tickets number of tickets to purchase.
	* @return bool return true if the transaction is valid.
	*/
	bool PurchaseSuccessful(string line, int num_tickets);

	/**
	* Checks to see if the event is found and if there are tickets left.
	*
	* @param event_title name of event.
	* @param seller_username name of seller.
	* @param num_tickets number of tickets to purchase.
	* @return bool true if tickets are available for purchase.
	*/
	bool TicketsFound(string event_title, string seller_username, int num_tickets);

	/**
	* Checks to see if the given input is valid.
	*
	* @param data_type type of data the value is, i.e. username
	* @param value string value of the data.
	* @return bool true if the data is valid.
	*/
	bool IsValid(string data_type, string value);
public:
	const int kSellTransactionCode = 3;
	const int kBuyTransactionCode = 4;
	const double kMaxTicketPrice = 999.99;
	const double kMaxNumTickets = 100;

	/**
	* Initializes a TicketTransaction for an account, and saves the name
	* of the tickets file for later use.
	*
	* @param account account that wants to do a transaction.
	* @param tickets_file name of the tickets file.
	*/
	TicketTransaction(Account account, string tickets_file);

	/**
	* Executes the program logic for a TicketTransaction based on
	* the transaction code.
	*
	* @param transaction_code unique transaction code identifier.
	* @return Account updated details after transaction is executed.
	*/
	Account Execute(int transaction_code);
};
