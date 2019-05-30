#include "RefundTransaction.h"

void RefundTransaction::SaveToOutput(int transaction_code, string file_name, Account* account) {
	// Open the file and write to it via adding.
	ofstream myfile;
	myfile.open(file_name, std::ios_base::app);

	string x = Padd_Spaces(kKeyTransactionCode, to_string(transaction_code));
	string u = Padd_Spaces(kKeyUsername, buyer_username_);
	string s = Padd_Spaces(kKeyUsername, seller_username_);
	// Ensure credits is saved in proper format
	string c = Padd_Spaces(kKeyCredits, CreditToString(credit_));

	// Insert a space between each padded value.
	myfile << x << " " << u << " " << s << " " << c << endl;
	myfile.close();
}

bool RefundTransaction::ValidUsername(string username) {
	if (!username.empty() && (username.length() <= kUsernameLength) && !IsDeleted(username)) {
		return true;
	}
	return false;
}

void RefundTransaction::AttemptRefund(string buyer_username, string seller_username, double credit) {
	// If input is valid
  if ((credit > 0) && ValidUsername(buyer_username) && ValidUsername(seller_username)) {
		string seller_info = GetAccountDetails(current_user_accounts_file_, seller_username);
		double seller_credit = atof(ParseAccountData(kKeyCredits, seller_info).c_str());
		// If seller has enough credits
		if (seller_credit >= credit) {
			string buyer_info = GetAccountDetails(current_user_accounts_file_, buyer_username);
			// Confirm that buyer is not a sell standard account
			if (ParseAccountData(kKeyAccount, buyer_info) != SELL_STANDARD_CODE) {
				SaveToOutput(kRefundTransactionCode, kOutputFileName, NULL);
				return;
			}
		}
	}
	ErrorMessage();
}

RefundTransaction::RefundTransaction(Account current_user, string current_user_accounts_file) {
    account_= current_user;
    current_user_accounts_file_ = current_user_accounts_file;
}

Account RefundTransaction::Execute(int transaction_code) {
    // refund transaction
    if (transaction_code == kRefundTransactionCode) {
	      cout << "Enter the buyer's username: " << endl;
	      cin >> buyer_username_;
	      cout << "Enter the seller's username: " << endl;
	      cin >> seller_username_;
	      cout << "Enter the amount to refund: " << endl;
				string temp;
				cin.ignore();
				getline(cin, temp);
				stringstream(temp) >> credit_;

				AttemptRefund(buyer_username_, seller_username_, credit_);
    }
    return account_;
}
