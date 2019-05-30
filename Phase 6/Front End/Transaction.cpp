#include "Transaction.h"

void Transaction::ErrorMessage() {
	cout << "Invalid input, returned to main. Please enter a command.\n";
}

bool Transaction::IsDeleted(string username) {
	// Read in the deleted user file line by line.
	ifstream file(kDeletedUserFileName);
	string line;
	// Stop when there are no more lines or if we reach the
	// bottom of the file.
	while (getline(file, line) && (line != kKeyEnd)) {
		// If the username is in the deleted list, output error.
		if (line == username) {
			cout << "Error: This account has been deleted.\n";
			return true;
		}
	}
	return false;
}

string Transaction::ToUpper(string word) {
	string uppercase_word = "";
	for (char c : word) {
		uppercase_word += toupper(c);
	}
	return uppercase_word;
}

string Transaction::CreditToString(double credit) {
	stringstream stream;
	stream << fixed << setprecision(2) << credit;
	return stream.str();
}

string Transaction::Padd_Spaces(string data_type, string value) {
	int specified_length_of_value = 0;
	string padded_value = "";
	string padding_character = " ";
	bool pad_right = true;
	bool numerical = false;

	// Initializes the appropriate specified length.
	if (data_type == kKeyTransactionCode) {
		specified_length_of_value = kTransactionCodeLength;
		numerical = true;
	}
	else if (data_type == kKeyEventName) {
		specified_length_of_value = kEventNameLength;
	}
	else if (data_type == kKeyUsername) {
		specified_length_of_value = kUsernameLength;
	}
	else if (data_type == kKeyNumberOfTickets) {
		specified_length_of_value = kTicketsLength;
		numerical = true;
	}
	else if (data_type == kKeyTicketPrice) {
		specified_length_of_value = kPriceLength;
		numerical = true;
	}
	else if (data_type == kKeyCredits) {
		specified_length_of_value = kCreditsLength;
		numerical = true;
	}

	// If the type of data is numerical, pad from the left,
	// and pad with zeroes instead of spaces.
	if (numerical) {
		pad_right = false;
		padding_character = "0";
	}

	// Calculates the necessary padding.
	int padding = specified_length_of_value - value.length();

	// Pads the word from either the right or the left.
	if (pad_right) {
		padded_value += value;
		for (int i = 0; i < padding; i++) {
			padded_value += padding_character;
		}
	}
	else if (!pad_right) {
		for (int i = padding; i > 0; i--) {
			padded_value += padding_character;
		}
		padded_value += value;
	}
	return padded_value;
}

string Transaction::ParseAccountData(string data_type, string line) {
	int i = kUsernameLength;
	int offset = 0;

	// Calculate the offset based off the format of the file.
	if (data_type == kKeyAccount) {
		return line.substr(kUsernameLength + 1, kAccountTypeLength);
	} else if (data_type == kKeyCredits) {
		return line.substr(line.length() - kCreditsLength);
	}

	// Returns the appropriate value without trailing whitespace.
	// Applies to string data types only, i.e. username.
	for (i; i > offset + 1; i--) {
		if (line.at(i) != ' ') {
			return line.substr(offset, i - offset + 1);
		}
	}

	// This line should never be reached.
	return "";
}

string Transaction::GetAccountDetails(string file_name, string username) {
	// If the username is not deleted, search through the file for it.
	if(!IsDeleted(username)) {
		ifstream file(file_name);
		string line;
		while (getline(file, line) && (line != kKeyEnd)) {
			// If the username is found, return the line of information.
			if (ParseAccountData(kKeyUsername, line) == username) {
				return line;
			}
		}
	}
	return "";
}
