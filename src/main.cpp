// main.cpp
// Console user interface for the Mobile Contact List Management System.
//
// Usage:  ./contacts [data-file]      (default data file: contacts.txt)

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "ContactBook.h"
#include "Validation.h"

using namespace std;

namespace {

// Result of asking the user for one value.
enum class Input { Ok, Cancel, Eof };

// Prints a prompt and reads one trimmed line. Returns false on end of input.
bool readLine(const string& prompt, string& out) {
    cout << prompt << flush;
    if (!getline(cin, out)) return false;
    out = validation::trim(out);
    return true;
}

// ---- Field prompts -------------------------------------------------------
// `keep` is used by "update": pressing Enter keeps the current value.
// Without `keep`, an empty name/number cancels the operation.

Input askName(const string& prompt, string& out, const string* keep = nullptr) {
    while (true) {
        string text;
        if (!readLine(prompt, text)) return Input::Eof;
        if (text.empty()) {
            if (keep != nullptr) {
                out = *keep;
                return Input::Ok;
            }
            return Input::Cancel;
        }
        string error;
        if (validation::validName(text, error)) {
            out = text;
            return Input::Ok;
        }
        cout << "  ! " << error << "\n";
    }
}

Input askPhone(const string& prompt, string& out, const string* keep = nullptr) {
    while (true) {
        string text;
        if (!readLine(prompt, text)) return Input::Eof;
        if (text.empty()) {
            if (keep != nullptr) {
                out = *keep;
                return Input::Ok;
            }
            return Input::Cancel;
        }
        string error;
        if (validation::normalizePhone(text, out, error)) return Input::Ok;
        cout << "  ! " << error << "\n";
    }
}

// Email is optional. On update: Enter keeps the old value, "-" clears it.
Input askEmail(const string& prompt, string& out, const string* keep = nullptr) {
    while (true) {
        string text;
        if (!readLine(prompt, text)) return Input::Eof;
        if (text.empty()) {
            out = (keep != nullptr) ? *keep : "";
            return Input::Ok;
        }
        if (keep != nullptr && text == "-") {
            out = "";
            return Input::Ok;
        }
        string error;
        if (validation::validEmail(text, error)) {
            out = text;
            return Input::Ok;
        }
        cout << "  ! " << error << "\n";
    }
}

// ---- Output helpers ------------------------------------------------------

void printTable(const vector<ContactNode*>& nodes) {
    cout << "\n" << left << setw(5) << "#" << setw(28) << "Name" << setw(18) << "Mobile"
         << "Email\n";
    cout << string(75, '-') << "\n";
    int index = 1;
    for (const ContactNode* node : nodes) {
        cout << left << setw(5) << index++ << setw(28) << node->data.name << setw(18)
             << node->data.phone << node->data.email << "\n";
    }
    cout << "\n";
}

void saveOrWarn(const ContactBook& book, const string& file) {
    if (!book.saveToFile(file)) {
        cout << "  ! Warning: could not save to '" << file << "'. Changes are only in memory.\n";
    }
}

// Let the user pick one contact by name or number. Returns nullptr if nothing
// was chosen (not found, cancelled or invalid choice).
ContactNode* selectContact(const ContactBook& book, const string& action) {
    string query;
    if (!readLine("Name or mobile number of the contact to " + action + ": ", query)) return nullptr;
    if (query.empty()) {
        cout << "Cancelled.\n";
        return nullptr;
    }

    // A number -> use the BST index.
    if (validation::looksLikePhone(query)) {
        string phone, error;
        if (!validation::normalizePhone(query, phone, error)) {
            cout << "  ! " << error << "\n";
            return nullptr;
        }
        ContactNode* node = book.findByPhone(phone);
        if (node == nullptr) cout << "No contact with that number.\n";
        return node;
    }

    // Otherwise search by name.
    vector<ContactNode*> matches = book.findByName(query);
    if (matches.empty()) {
        cout << "No contact found for \"" << query << "\".\n";
        return nullptr;
    }
    if (matches.size() == 1) return matches[0];

    cout << matches.size() << " contacts match:\n";
    printTable(matches);
    string choice;
    if (!readLine("Choose a number (1-" + to_string(matches.size()) + "): ", choice)) return nullptr;
    try {
        size_t used = 0;
        int number = stoi(choice, &used);
        if (used == choice.size() && number >= 1 && number <= static_cast<int>(matches.size())) {
            return matches[number - 1];
        }
    } catch (...) {
        // fall through to the message below
    }
    cout << "  ! Invalid choice.\n";
    return nullptr;
}

// ---- Menu actions --------------------------------------------------------

void addContact(ContactBook& book, const string& file) {
    cout << "\n--- Add contact (leave name or number empty to cancel) ---\n";
    Contact contact;

    Input result = askName("Name: ", contact.name);
    if (result != Input::Ok) {
        if (result == Input::Cancel) cout << "Cancelled.\n";
        return;
    }
    result = askPhone("Mobile number: ", contact.phone);
    if (result != Input::Ok) {
        if (result == Input::Cancel) cout << "Cancelled.\n";
        return;
    }
    if (askEmail("Email (optional): ", contact.email) == Input::Eof) return;

    string error;
    if (book.add(contact, error)) {
        cout << "Contact added: " << contact.name << " (" << contact.phone << ")\n";
        saveOrWarn(book, file);
    } else {
        cout << "  ! " << error << "\n";
    }
}

void deleteContact(ContactBook& book, const string& file) {
    cout << "\n--- Delete contact ---\n";
    ContactNode* node = selectContact(book, "delete");
    if (node == nullptr) return;

    cout << "Selected: " << node->data.name << "  " << node->data.phone << "\n";
    string answer;
    if (!readLine("Delete this contact? (y/n): ", answer)) return;
    if (validation::toLower(answer) != "y") {
        cout << "Nothing deleted.\n";
        return;
    }

    string name = node->data.name;  // copy: the node is freed by remove()
    if (book.remove(node)) {
        cout << "Deleted " << name << ".\n";
        saveOrWarn(book, file);
    }
}

void updateContact(ContactBook& book, const string& file) {
    cout << "\n--- Update contact ---\n";
    ContactNode* node = selectContact(book, "update");
    if (node == nullptr) return;

    Contact current = node->data;
    cout << "Editing " << current.name << "  " << current.phone << "  " << current.email << "\n";
    cout << "(press Enter to keep a value; type - to clear the email)\n";

    Contact updated;
    if (askName("Name [" + current.name + "]: ", updated.name, &current.name) == Input::Eof) return;
    if (askPhone("Mobile [" + current.phone + "]: ", updated.phone, &current.phone) == Input::Eof) return;
    if (askEmail("Email [" + current.email + "]: ", updated.email, &current.email) == Input::Eof) return;

    string error;
    if (book.update(node, updated, error)) {
        cout << "Contact updated.\n";
        saveOrWarn(book, file);
    } else {
        cout << "  ! " << error << "\n";
    }
}

void searchByName(const ContactBook& book) {
    cout << "\n--- Search by name ---\n";
    string keyword;
    if (!readLine("Name (or part of it): ", keyword)) return;
    if (keyword.empty()) {
        cout << "Cancelled.\n";
        return;
    }
    vector<ContactNode*> matches = book.findByName(keyword);
    if (matches.empty()) {
        cout << "No contact found for \"" << keyword << "\".\n";
        return;
    }
    cout << matches.size() << " contact(s) found:";
    printTable(matches);
}

void searchByPhone(const ContactBook& book) {
    cout << "\n--- Search by mobile number ---\n";
    string text;
    if (!readLine("Mobile number: ", text)) return;
    if (text.empty()) {
        cout << "Cancelled.\n";
        return;
    }
    string phone, error;
    if (!validation::normalizePhone(text, phone, error)) {
        cout << "  ! " << error << "\n";
        return;
    }
    ContactNode* node = book.findByPhone(phone);
    if (node == nullptr) {
        cout << "No contact with the number " << phone << ".\n";
        return;
    }
    cout << "1 contact found:";
    printTable({node});
}

void displayAll(const ContactBook& book) {
    cout << "\n--- All contacts (sorted by name) ---\n";
    if (book.count() == 0) {
        cout << "The contact list is empty.\n";
        return;
    }
    vector<ContactNode*> all;
    for (ContactNode* node = book.first(); node != nullptr; node = node->next) all.push_back(node);
    printTable(all);
    cout << "Total: " << book.count() << " contact(s)\n";
}

void undoLast(ContactBook& book, const string& file) {
    string message;
    if (book.undo(message)) {
        cout << message << "\n";
        saveOrWarn(book, file);
    } else {
        cout << message << "\n";
    }
}

void showActivity(const ContactBook& book) {
    cout << "\n--- Recent activity (oldest first, last " << ActivityQueue::CAPACITY << ") ---\n";
    vector<string> entries = book.recentActivity();
    if (entries.empty()) {
        cout << "No activity in this session yet.\n";
        return;
    }
    for (const string& entry : entries) cout << "  " << entry << "\n";
}

void printMenu() {
    cout << "\n=========================================\n"
         << "   MOBILE CONTACT LIST MANAGEMENT SYSTEM\n"
         << "=========================================\n"
         << " 1. Add contact\n"
         << " 2. Delete contact\n"
         << " 3. Update contact\n"
         << " 4. Search by name\n"
         << " 5. Search by mobile number\n"
         << " 6. Display all contacts\n"
         << " 7. Count contacts\n"
         << " 8. Undo last change\n"
         << " 9. Recent activity\n"
         << " 0. Save and exit\n"
         << "-----------------------------------------\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    const string file = (argc > 1) ? argv[1] : "contacts.txt";

    ContactBook book;
    int skipped = 0;
    int loaded = book.loadFromFile(file, skipped);
    cout << "Loaded " << loaded << " contact(s) from '" << file << "'.";
    if (skipped > 0) cout << " (" << skipped << " invalid or duplicate line(s) skipped)";
    cout << "\n";

    while (true) {
        printMenu();
        string choice;
        if (!readLine("Choose an option: ", choice)) break;  // end of input -> save and exit

        if (choice == "1") {
            addContact(book, file);
        } else if (choice == "2") {
            deleteContact(book, file);
        } else if (choice == "3") {
            updateContact(book, file);
        } else if (choice == "4") {
            searchByName(book);
        } else if (choice == "5") {
            searchByPhone(book);
        } else if (choice == "6") {
            displayAll(book);
        } else if (choice == "7") {
            cout << "\nNumber of contacts: " << book.count() << "\n";
        } else if (choice == "8") {
            undoLast(book, file);
        } else if (choice == "9") {
            showActivity(book);
        } else if (choice == "0") {
            break;
        } else {
            cout << "  ! Invalid option. Please enter a number from 0 to 9.\n";
        }
    }

    if (book.saveToFile(file)) {
        cout << "\nContacts saved to '" << file << "'. Goodbye!\n";
    } else {
        cout << "\n  ! Could not save to '" << file << "'. Goodbye!\n";
        return 1;
    }
    return 0;
}
