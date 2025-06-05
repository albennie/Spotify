#include "Admin.h"

Admin::Admin() : Account("admin", "admin123") {}

bool Admin::login(const string& u, const string& p) const {
    return u == username && p == password;
}