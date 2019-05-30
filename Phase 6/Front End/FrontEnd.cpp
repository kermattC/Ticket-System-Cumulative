#include <iostream>
#include <string>
#include <fstream>

#include "Account.h"
#include "LoginTransaction.h"
#include "BasicTransaction.h"
#include "TicketTransaction.h"
#include "RefundTransaction.h"

using namespace std;

/**
* FrontEnd
* This is the main program logic, and puts together all relevant classes
* to run the front end.
*
* @author Stephanie Phung
* @author Matt Chan
* @version 2.0
*/
int main(int argc, char* argv[]) {
	// If there are insufficient command line parameters, exit the program.
	if (argc != 3) {
		return 1;
	}

	// Initializes constants.
	const string kExitKeyword = "exit";
	const string kPrompt = "> "; // this just lets the user know when they can enter input

	// Initializes local variables.
	string current_user_accounts_file = argv[1]; // "current_user_accounts.data"
	string tickets_file = argv[2]; // "available_tickets.data"
	bool is_logged_in = false;


	Account current_user;

	// Keep running the program until the user decides to exit using the exit keyword.
	bool running = true;
	do {
		string command, username;
		cout << kPrompt;
		cin >> command;

		// Do the appropriate action based on the command.
		if (command == kExitKeyword) {
			running = false;
		} else if (!is_logged_in) { // If not logged in, only accept login command.
			if (command == "login") {
				// Create a login transaction and execute it, saving current account here.
				LoginTransaction login_transaction(current_user_accounts_file);
				current_user = login_transaction.Execute(login_transaction.kLoginTransactionCode);
				if (current_user.GetName() != "") {
					cout << "Welcome, " << current_user.GetName() << "!\n";
					is_logged_in = true;
				}
			}
		} else if (is_logged_in) { // If logged in, accept all other commands.
			if (command == "logout") {
				// Create a basic transaction to execute logout.
				BasicTransaction logout_transaction(current_user, current_user_accounts_file);
				current_user = logout_transaction.Execute(logout_transaction.kEndSessionTransactionCode);
				cout << "Logout successful.\n";
				is_logged_in = false;
			} else if (command == "addcredit") {
				BasicTransaction addcredit_transaction(current_user, current_user_accounts_file);
				current_user = addcredit_transaction.Execute(addcredit_transaction.kAddCreditTransactionCode);
		  } else if ((command == "refund") && (current_user.GetType() == ADMIN_CODE)){
				// Create a refund transaction
				 RefundTransaction refund_transaction(current_user, current_user_accounts_file);
				 current_user = refund_transaction.Execute(refund_transaction.kRefundTransactionCode);
			} else if ((command == "buy") && (current_user.GetType() != SELL_STANDARD_CODE)) { // can only buy if not a seller
				// Create a ticket transaction and execute it, getting updated account data back.
				TicketTransaction buy_transaction(current_user, tickets_file);
				current_user = buy_transaction.Execute(buy_transaction.kBuyTransactionCode);
			} else if ((command == "sell") && (current_user.GetType() != BUY_STANDARD_CODE)) {
				TicketTransaction sell_transaction(current_user, tickets_file);
				current_user = sell_transaction.Execute(sell_transaction.kSellTransactionCode);
			} else if ((command == "create") && (current_user.GetType() == ADMIN_CODE)){
				BasicTransaction create_transaction(current_user, current_user_accounts_file);
				current_user = create_transaction.Execute(create_transaction.kCreateTransactionCode);
			} else if ((command == "delete") && (current_user.GetType() == ADMIN_CODE)){
				BasicTransaction delete_transaction(current_user, current_user_accounts_file);
				current_user = delete_transaction.Execute(delete_transaction.kDeleteTransactionCode);
			} else if ((current_user.GetType() != ADMIN_CODE) &&
								((command == "delete") || (command == "refund") || (command == "create"))) {
			    cout << "You must be an admin to run this command.\n";
			}
		}
	} while (running);
	cout << "Goodbye.\n";
	return 0;
}
