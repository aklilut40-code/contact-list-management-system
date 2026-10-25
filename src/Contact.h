// Contact.h
// The plain record stored for every entry in the contact list.
#pragma once

#include <string>

using namespace std;

struct Contact {
    string name;   // display name, e.g. "Abel Tesfay"
    string phone;  // normalized mobile number, e.g. "+251911000101" (unique key)
    string email;  // optional, may be empty
};
