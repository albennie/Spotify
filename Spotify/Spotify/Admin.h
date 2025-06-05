#pragma once
#include <string>
#include "Account.h"
using namespace std;

class Admin : public Account {
public:
    Admin();
    bool login(const string& u, const string& p) const;
};