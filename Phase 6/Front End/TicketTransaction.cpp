#include "TicketTransaction.h"

void TicketTransaction::SaveToOutput(int transaction_code, string file_name, Account* account) {
	// Open the file and write to it via adding.
	ofstream myfile;
	myfile.open(file_name, std::ios_base::app);

	string x = Padd_Spaces(kKeyTransactionCode, to_string(transaction_code));
	string e = Padd_Spaces(kKeyEventName, event_title_);
	string s = Padd_Spaces(kKeyUsername, seller_username_);
	string t = Padd_Spaces(kKeyNumberOfTickets, to_string(num_tickets_));
	string p = Padd_Spaces(kKeyTicketPrice, CreditToString(ticket_price_));

	// Insert a space between each padded value.
	myfile << x << " " << e << " " << s << " " << t << " " << p << endl;
	myfile.close();
}

string TicketTransaction::ParseData(string data_type, string line) {
	int i = kEventNameLength;
	int offset = 0;

	// Calculate the offset based off the format of the file.
	if (data_type == kKeyUsername) {
		offset = i + 1;
		i = offset + kUsernameLength;
	}

	// Returns the appropriate value without trailing whitespace.
	for (i; i > offset + 1; i--) {
		if (line.at(i) != ' ') {
			return line.substr(offset, i - offset + 1);
		}
	}

	// This line should never be reached.
	return "";
}

bool TicketTransaction::PurchaseSuccessful(string line, int num_tickets) {
	// Offsets are calculated by following the format of the tickets data file.
	int offset_tickets = kEventNameLength + 1 + kUsernameLength + 1;
	int offset_price = offset_tickets + kTicketsLength + 1;

	int available_tickets = stoi(line.substr(offset_tickets, kTicketsLength + 1));
	// If there are not enough tickets, print an error message and return false.
	if (available_tickets < num_tickets) {
		ErrorMessage();
		return false;
	}

	// Saves the ticket price to the current TicketTransaction.
	ticket_price_ = stod(line.substr(offset_price, kPriceLength + 1));

	// Print out the cost information and ask for confirmation.
	cout << "Cost per ticket = " << ticket_price_ << endl;
	double total_cost = ticket_price_ * num_tickets;
	cout << "Total cost = " << total_cost << endl;
	char confirm;
	cout << "Confirm? (y/n)\n";
	cin >> confirm;
	// If the confirmation is not 'y', return false.
	if (confirm != 'y') {
		return false;
	}

	// If the account does not have enough credits, print out message.
	if (account_.GetCredit() < total_cost) {
		cout << "You do not have enough credits to make this purchase.\n";
		return false;
	} else { // If there are enough credits, pay for the tickets.
		account_.SetCredit(account_.GetCredit() - total_cost);
	}

	// Otherwise, tickets were purchased successfully.
	cout << "Tickets purchased successfully.\n";
	return true;
}

bool TicketTransaction::TicketsFound(string event_title, string seller_username, int num_tickets) {
	// If any of the inputs are incorrect length or format, reject it automatically.
	if ((event_title.length() > kEventNameLength) ||
	  (IsDeleted(seller_username)) ||
		(seller_username == account_.GetName()) ||
		(seller_username.length() > kUsernameLength) ||
		(num_tickets <= 0) ||
		((account_.GetType() != ADMIN_CODE) && (num_tickets > 4))) {
		ErrorMessage();
		return false;
	}

	// Read in the tickets file line by line until we get to the end.
	ifstream file(tickets_file_);
	string line;
	while (getline(file, line) && (line != kKeyEnd)) {
		// If the event title and username exist on the same line, try saving the ticket data.
		if ((ParseData(kKeyEventName, line) == event_title) && (ParseData(kKeyUsername, line) == seller_username)) {
			return PurchaseSuccessful(line, num_tickets);
		}
	}

	// If the event does not exist, print an error message and return false.
	ErrorMessage();
	return false;
}

bool TicketTransaction::IsValid(string data_type, string value) {
	if (data_type == kKeyEventName) {
		if ((value.length() <= kEventNameLength) &&
				(!value.empty())) {
			// Make sure the name of the event is not just whitespace.
			for (int i = 0; i < value.length(); i++) {
				if (value[i] != ' ') {
					return true;
				}
			}
		}
	} else if (data_type == kKeyTicketPrice) {
		double price = atof(value.c_str());
		if ((price >= 0) && (price <= kMaxTicketPrice)) {
			return true;
		}
	} else if (data_type == kKeyNumberOfTickets) {
		double n = atof(value.c_str());
		if ((n > 0) && (n <= kMaxNumTickets) && (n == (int)n)) {
			return true;
		}
	}
	cout << "Invalid input.\n";
	return false;
}

TicketTransaction::TicketTransaction(Account account, string tickets_file) {
	account_ = account;
	tickets_file_ = tickets_file;
}

Account TicketTransaction::Execute(int transaction_code) {
	if (transaction_code == kBuyTransactionCode) {
		cout << "Please enter the event title:\n> ";
		cin.ignore();
		getline(cin, event_title_);

		cout << "Please enter the number of tickets to purchase:\n> ";
		string temp;
		// Uses a getline to avoid invalid input.
		getline(cin, temp);
		// Stringstream ensures valid conversion from string to int.
		stringstream(temp) >> num_tickets_;

		cout << "Please enter the seller's username:\n> ";
		getline(cin, seller_username_);

		if (TicketsFound(event_title_, seller_username_, num_tickets_)) {
			SaveToOutput(transaction_code, kOutputFileName, NULL);
		}
	} else if (transaction_code == kSellTransactionCode) {
		do {
			cout << "Please enter the event title:\n> ";
			getline(cin, event_title_);
		} while (!IsValid(kKeyEventName, event_title_));

		string temp;
		do {
			cout << "Please enter the price per ticket:\n> ";
			// Uses a getline to avoid invalid input.
			getline(cin, temp);
			// Stringstream ensures valid conversion from string to int.
			stringstream(temp) >> ticket_price_;
		} while (!IsValid(kKeyTicketPrice, temp));

		do {
			cout << "Please enter the number of tickets to sell:\n> ";
			getline(cin, temp);
			stringstream(temp) >> num_tickets_;
		} while (!IsValid(kKeyNumberOfTickets, temp));

		seller_username_ = account_.GetName();
		cout << "Event successfully created.\n";
		SaveToOutput(transaction_code, kOutputFileName, NULL);
	}

	return account_;
}
