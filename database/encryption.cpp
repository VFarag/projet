#include "encryption.hpp"

#include <bitset>

using namespace std;


Password::Password(string &password, bool is_encrypted):
    _raw_value(password) {
        if (is_encrypted) {_encrypted_value = password;}
        else {encrypt(password);}
    }

void Password::encrypt(const string &password) {
    string encrypted_password;
    for (char c: password) {
        encrypted_password.append(c + "");
    }
    _encrypted_value = encrypted_password;
}

string Password::str() {
    return _encrypted_value;
}

bool Password::operator==(const string &str) const {
    return str == _encrypted_value;
}

bool Password::operator==(const Password &other) const {
    return _encrypted_value == other._encrypted_value;
}

ostream &operator<<(ostream &os, const Password &p) {
    os << p._encrypted_value;
    return os;
}
