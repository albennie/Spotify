#pragma once
#include <string>
using namespace std;

class Account {
protected:
    string username;
    string password;
public:
    Account(string u = "", string p = "");
    string getUsername() const;
    string getPassword() const;
    void setUsername(const string& u);
    void setPassword(const string& p);
};