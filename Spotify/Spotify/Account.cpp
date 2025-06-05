#include "Account.h"

Account::Account(string u, string p) : username(u), password(p) {}

string Account::getUsername() const {
    return username;
}

string Account::getPassword() const {
    return password;
}

void Account::setUsername(const string& u) {
    username = u;
}

void Account::setPassword(const string& p) {
    password = p;
}