#include "Account.h"

Account::Account() {
}

Account::Account(string username, string account_type, double credit) {
	username_ = username;
	account_type_ = account_type;
	credit_ = credit;
}

string Account::GetName() {
	return username_;
}

string Account::GetType() {
	return account_type_;
}

double Account::GetCredit() {
	return credit_;
}

void Account::SetName(string username) {
	username_ = username;
}

void Account::SetType(string account_type) {
	account_type_ = account_type;
}

void Account::SetCredit(double credit) {
	credit_ = credit;
}
