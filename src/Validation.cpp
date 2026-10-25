// Validation.cpp
#include "Validation.h"

#include <cctype>

using namespace std;

namespace validation {

static const size_t MAX_NAME_LENGTH = 40;
static const size_t MAX_EMAIL_LENGTH = 40;

string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) ++start;
    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}

string toLower(const string& s) {
    string out = s;
    for (char& c : out) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return out;
}

bool validName(const string& name, string& error) {
    if (name.empty()) {
        error = "Name cannot be empty.";
        return false;
    }
    if (name.size() > MAX_NAME_LENGTH) {
        error = "Name is too long (maximum 40 characters).";
        return false;
    }
    for (char c : name) {
        if (c == '|') {
            error = "Name cannot contain the '|' character.";
            return false;
        }
        if (iscntrl(static_cast<unsigned char>(c))) {
            error = "Name contains an invalid character.";
            return false;
        }
    }
    return true;
}

bool normalizePhone(const string& input, string& normalized, string& error) {
    // 1. Strip common separators.
    string cleaned;
    for (char c : input) {
        if (c == ' ' || c == '-' || c == '.' || c == '(' || c == ')') continue;
        cleaned += c;
    }

    // 2. Optional leading '+', everything else must be a digit.
    bool hasPlus = !cleaned.empty() && cleaned[0] == '+';
    string digits = hasPlus ? cleaned.substr(1) : cleaned;
    if (digits.empty()) {
        error = "Mobile number cannot be empty.";
        return false;
    }
    for (char c : digits) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            error = "Mobile number may only contain digits (and a leading '+').";
            return false;
        }
    }

    // 3. Convert Ethiopian formats to the international form.
    if (!hasPlus && digits.size() == 10 && (digits.compare(0, 2, "09") == 0 || digits.compare(0, 2, "07") == 0)) {
        digits = "251" + digits.substr(1);
        hasPlus = true;
    } else if (!hasPlus && digits.size() == 12 && digits.compare(0, 3, "251") == 0) {
        hasPlus = true;
    }

    // 4. Length check (E.164 allows at most 15 digits).
    if (digits.size() < 7 || digits.size() > 15) {
        error = "Mobile number must have between 7 and 15 digits.";
        return false;
    }

    normalized = (hasPlus ? "+" : "") + digits;
    return true;
}

bool validEmail(const string& email, string& error) {
    if (email.empty()) return true;  // optional field

    if (email.size() > MAX_EMAIL_LENGTH) {
        error = "Email is too long (maximum 40 characters).";
        return false;
    }
    size_t at = email.find('@');
    if (at == string::npos || at == 0 || email.find('@', at + 1) != string::npos) {
        error = "Email must look like name@domain.com.";
        return false;
    }
    string domain = email.substr(at + 1);
    size_t dot = domain.find('.');
    if (dot == string::npos || dot == 0 || domain.back() == '.') {
        error = "Email must look like name@domain.com.";
        return false;
    }
    for (char c : email) {
        if (isspace(static_cast<unsigned char>(c)) || c == '|') {
            error = "Email contains an invalid character.";
            return false;
        }
    }
    return true;
}

bool looksLikePhone(const string& s) {
    bool hasDigit = false;
    for (char c : s) {
        if (isalpha(static_cast<unsigned char>(c))) return false;
        if (isdigit(static_cast<unsigned char>(c))) hasDigit = true;
    }
    return hasDigit;
}

}  // namespace validation
