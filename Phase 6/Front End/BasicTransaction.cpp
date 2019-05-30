#include "BasicTransaction.h"
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

void BasicTransaction::SaveToOutput(int transaction_code, string file_name, Account* account) {
	// Open the file and write to it via adding.
	ofstream my_file;
	my_file.open(file_name, std::ios_base::app);

	string x = Padd_Spaces(kKeyTransactionCode, to_string(transaction_code));

	string u, t, c;
	if (account == NULL) {
		u = Padd_Spaces(kKeyUsername, account_.GetName());
		t = Padd_Spaces(kKeyAccount, account_.GetType());
		c = Padd_Spaces(kKeyCredits, CreditToString(account_.GetCredit()));
	} else {
		u = Padd_Spaces(kKeyUsername, account->GetName());
		t = Padd_Spaces(kKeyAccount, account->GetType());
		c = Padd_Spaces(kKeyCredits, CreditToString(account->GetCredit()));
	}

	// Insert a space between each padded value.
	my_file << x << " " << u << " " << t << " " << c << endl;
	my_file.close();
}

BasicTransaction::BasicTransaction(Account account, string current_user_accounts_file) {
	account_ = account;
	current_user_accounts_file_ = current_user_accounts_file;
}

// check that the lengths of the inputs are within the limit, such as username, account type and credit
bool BasicTransaction::IsValidCreate(string username, string account_type, double credit){
	string scredit = CreditToString(credit);
    if ((username.length() > kUsernameLength) ||
		(account_type.length() > kAccountTypeLength) ||
		(scredit.length() > kCreditsLength)) {
		ErrorMessage();
		return false;
	}
	return true;
}

// check that the username length is wthin the limit
bool BasicTransaction::IsValidDelete(string username){
	if ((username.length() > kUsernameLength)){
		ErrorMessage();
		return false;
	}
	return true;
}

void BasicTransaction::Create(string new_account_name, string new_account_type, double new_account_credit){
	string account_name = Padd_Spaces(kKeyUsername, new_account_name);
	string account_type = Padd_Spaces(kKeyAccount, new_account_type);
	string account_credit = Padd_Spaces(kKeyCredits, CreditToString(new_account_credit));

	ifstream in_file;
	ofstream out_file;
	string line;

	bool deleted = false;
	bool found = false;
	bool valid_name = true;
	bool valid_credit = true;
	bool valid_type = true;

	// check if the username already exists. if it does then the create transaction
	// will be rejected
	in_file.open(current_user_accounts_file_ );
		if (in_file.is_open()){
			while (getline(in_file, line)){
				if (Compare(line, new_account_name)){
					found = true;
				}
			}
		}

	// check if the username exists in the deleted users file. if it does then the create transaction
	// will be rejected
	in_file.open(kDeletedUserFileName);
	if (in_file.is_open()){
		while (getline(in_file, line)){
			if (Compare(line, new_account_name)){
				deleted = true;
			}
		}
	}

	// check that the user cannot create their own name
	if ((new_account_name == account_.GetName())){
		valid_name = false;
		cout << "Error: Cannot make the same username as your's. Please enter a different one" << endl;
	} else if (found){
		cout << "Error: Username is being used. Please enter a different one " << endl;
	}

	if (deleted){
		cout << "Error: Username has been deleted. Please enter a diferent one" << endl;
	}

	// an array of valid account types. Used to compare the inputted account type to see if it is valid
	string valid_account_types[] = {"AA", "aa", "Aa", "aA",
																	"BS", "bs", "bS", "Bs",
																	"FS", "fs", "fS", "Fs",
																	"SS", "ss", "sS", "Ss"};
	bool exists = std::find(std::begin(valid_account_types), std::end(valid_account_types), new_account_type) != std::end(valid_account_types);
	if (!exists){
		valid_type = false;
		cout << "Error: Invalid account type.\n";
	}
	// set the account type to upper case
	new_account_type = ToUpper(new_account_type);

	// check that the number of decimals are or less
	int digits = 0;
	double temp_account_credit = new_account_credit;
	while (temp_account_credit > 0){
		temp_account_credit = temp_account_credit / 10;
		digits ++;
	}

	// calculate the number of digits after the decimal. Method from stackoverflow, by Sev
	string s;
	string t;
	std::stringstream out;
	out << new_account_credit;
	s = out.str();

	t = s.substr(s.find(".")+1);
	if (t.length() > 2){
		valid_credit = false;
	}
	if ((s == t) && (new_account_credit >= 0) && (new_account_credit <=999999.99)) {
		valid_credit = true;
	}
	cout<<"number of decimal places: " << t.length() << endl;

	// perform the transaction once all conditions are met
	if ((!deleted) && (valid_credit) && (valid_name) && (!found) && (valid_type)){
		cout << "Created new user: " << new_account_name << endl;
		Account* new_user = new Account (new_account_name, new_account_type, new_account_credit);
		SaveToOutput(kCreateTransactionCode, kOutputFileName, new_user);
	}
}

void BasicTransaction::Delete(Account* account){
	ifstream in_file;
	ofstream out_file;
	string line;
	// if username exists in deleted_users.data
	bool exists = false;
	// to check if username exists in current_user_accounts.data
	bool found = false;

	// check if the username exists in the current_user_accounts.data file
	in_file.open(current_user_accounts_file_ );
	if (in_file.is_open()){
		while (getline(in_file, line)){
			if (Compare(line, account->GetName())){
				found = true;
			}
		}
	}
	in_file.close();

	// check if username already exists in deleted_users.data file
	in_file.open(kDeletedUserFileName);
	if (in_file.is_open()){
		while (getline(in_file, line) ){
			 if (line != "END"){
				if (Compare(line, account->GetName())){
				 	cout << "Error: " << account->GetName() << " has already been deleted" << endl;
					exists = true;
				}
			}
		}
		in_file.close();
	}

	// check that the selected username is not the same as the current user's
	if (account->GetName() == account_.GetName()){
		cout << "Error: You cannot delete yourself " << endl;
	}

	// error message if the user cannot be found in current_user_accounts.data
	if (!found){
		cout << "Error: " << account->GetName() << " cannot be found " << endl;
	}

	// write the username to the deleted usernames file
	if (!exists && found && (account->GetName() != account_.GetName())){
			// out_file.open("deleted_users.data", std::ios_base::app);
			// out_file << del_account_name << endl;
			// out_file.close();
			cout << "Deleted user: " << account->GetName() << endl;
			SaveToOutput(kDeleteTransactionCode, kOutputFileName, account);
	}
}

bool BasicTransaction::Compare(string line, string del_account_name){
	// loops through both strings to check if each character is the same
	// if the counter is the same length as the original character then
	// return true
	int counter = 0;
	for (int i = 0; i < del_account_name.length(); i++){
		if (line[i] == del_account_name[i]){
			counter++;
		}
	}
	if (counter == del_account_name.length()){
		return true;
	}
	return false;
}

void BasicTransaction::AddCreditsAndSave(Account* account, double amount) {
	// If the amount is within bounds, add to account and save to output.
	if ((amount > 0) && (amount <= kMaxCreditToAdd)) {
		account->SetCredit(account->GetCredit() + amount);
		SaveToOutput(kAddCreditTransactionCode, kOutputFileName, account);
		cout << "Transaction successful.\n";
	} else {
		ErrorMessage();
	}
}

Account BasicTransaction::Execute(int transaction_code) {
	string new_account_name;
	string new_account_type;
	double new_account_credit;
	string new_account_creditS;
	string del_account_name;
	bool valid_type = true;
	bool valid_credit = true;
	// If it's a logout transaction, save details to output
	// and return NULL.
	if (transaction_code == kEndSessionTransactionCode) {
		SaveToOutput(transaction_code, kOutputFileName, NULL);
		Account *p = &this->account_;
		p = NULL;

	} // create transaction
	else if (transaction_code == kCreateTransactionCode){
		cout << "Enter new account name: " << endl;
		cin >> new_account_name;
		cout << "Enter new account type:" << endl;
		cin.ignore();
		getline(cin, new_account_type);
		cout << "Enter new account balance: " << endl;
		cin >> new_account_credit;

		if (cin.fail()){
			valid_credit = false;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Need proper numbers for amount." << endl;
		}

		if (new_account_type.length() > kAccountTypeLength){
			valid_type = false;
		}
		if (IsValidCreate(new_account_name, new_account_type, new_account_credit)&& (valid_type) && (valid_credit)){
			Create(new_account_name, new_account_type, new_account_credit);
		}
	}
	// delete transaction
	else if (transaction_code == kDeleteTransactionCode){
			cin.ignore();
			Account* account = &account_;

			cout << "Enter account name: " << endl;
			getline(cin, del_account_name);
			string line = GetAccountDetails(current_user_accounts_file_, del_account_name);
				if (line != "") {
					string username = ParseAccountData(kKeyUsername, line);
					string account_type = ParseAccountData(kKeyAccount, line);
					double credit =	atof(ParseAccountData(kKeyCredits, line).c_str());
					account = new Account(username, account_type, credit);
				} else {
					return account_;
				}
				Delete(account);
	} // add credit transaction
	else if (transaction_code == kAddCreditTransactionCode) {
		cout << "Enter amount of credit to add:\n";
		cin.ignore();
		string temp;
		double amount;
		Account* account = &account_;

		// Uses a getline to avoid invalid input.
		getline(cin, temp);
		// Stringstream ensures valid conversion from string to double.
		stringstream(temp) >> amount;

		if (account_.GetType() == ADMIN_CODE) {
			cout << "Enter username of target user:\n";
			getline(cin, temp);
			// If the admin is adding to an account that is not their own
			if (temp != account_.GetName()) {
				// Get account details of the username
				string line = GetAccountDetails(current_user_accounts_file_, temp);
				// If the information is found
				if (line != "") {
					// Parse the data and create a temp account to add credits to
					string username = ParseAccountData(kKeyUsername, line);
					string account_type = ParseAccountData(kKeyAccount, line);
					double credit =	atof(ParseAccountData(kKeyCredits, line).c_str());
					account = new Account(username, account_type, credit);
				} else {
					return account_;
				}
			}
		}

		AddCreditsAndSave(account, amount);
	}
	return account_;
}
