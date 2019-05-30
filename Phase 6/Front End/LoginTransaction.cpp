#include "LoginTransaction.h"

void LoginTransaction::ErrorMessage() {
	cout << "Invalid username. Please try again.\n";
}

bool LoginTransaction::LoginSuccessful (string username) {
	// If the username is equal to the end keyword at the
	// bottom of the current user accounts file, return false.
	if (username.length() == kEndLength) {
		if (ToUpper(username) == kKeyEnd) {
			ErrorMessage();
			return false;
		}
	}

	// Check if the username exists in the deleted users file
	if (IsDeleted(username)) {
		return false;
	}

	// Read in the current user accounts file line by line.
	ifstream file(current_user_accounts_file_);
	string line;
	// Stop when there are no more lines or if we reach the
	// bottom of the file.
	while (getline(file, line) && (line != kKeyEnd)) {
		// If the username we are given exists in the file,
		// login is successful.
		if (ParseUsername(line) == username) {
			cout << "Login successful.\n";

			// Read in the information for the account and save it
			// so we can use it later. The offsets are generating by
			// following the format of the current user accounts file.
			this->account_.SetName(username);
			int account_type_offset = kUsernameLength + 1;
			this->account_.SetType(line.substr(account_type_offset, kAccountTypeLength));
			int credit_offset = account_type_offset + kAccountTypeLength + 1;
			this->account_.SetCredit(stod(line.substr(credit_offset, kCreditsLength)));

			return true;
		}
	}

	// Output an error message if the username is not found.
	ErrorMessage();
	return false;
}

string LoginTransaction::ParseUsername(string line) {
	// Reads from right to left to get rid of trailing whitespace.
	for (int i = kUsernameLength; i > 1; i--) {
		if (line.at(i) != ' ') {
			return line.substr(0, i + 1);
		}
	}
	return line;
}

void LoginTransaction::SaveToOutput(int transaction_code, string file_name, Account* account) {
}

LoginTransaction::LoginTransaction(string current_user_accounts_file) {
	current_user_accounts_file_ = current_user_accounts_file;
}

Account LoginTransaction::Execute(int transaction_code) {
	string username;
	cout << "Please enter your username:\n>";
	cin >> username;
	if(!LoginSuccessful(username)) {
		account_.SetName("");
	}
	return this->account_;
}
