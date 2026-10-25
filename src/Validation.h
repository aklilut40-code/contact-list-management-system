// Validation.h
// Input validation and small string helpers used across the program.
#pragma once

#include <string>

using namespace std;

namespace validation {

// Remove leading/trailing whitespace.
string trim(const string& s);

// Lower-case copy (ASCII), used for case-insensitive comparison.
string toLower(const string& s);

// Name: 1-40 characters, no '|' (file separator), no control characters.
bool validName(const string& name, string& error);

// Phone: accepts spaces, dashes, dots and brackets, then normalizes.
//   0911000101      -> +251911000101   (Ethiopian local format 09.. / 07..)
//   251911000101    -> +251911000101
//   +251 911 000101 -> +251911000101
// The result must be an optional '+' followed by 7-15 digits.
bool normalizePhone(const string& input, string& normalized, string& error);

// Email is optional: empty is valid. Otherwise needs a simple local@domain.tld shape.
bool validEmail(const string& email, string& error);

// True if the text has at least one digit and no letters (used to decide
// whether the user typed a number or a name).
bool looksLikePhone(const string& s);

}  // namespace validation
