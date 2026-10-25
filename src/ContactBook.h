// ContactBook.h
// Facade that ties the data structures together:
//
//   ContactList  (sorted linked list)  - the contacts, ordered by name
//   PhoneBST     (binary search tree)  - fast lookup by mobile number
//   UndoStack    (stack)               - undo the last changes
//   ActivityQueue(queue / array)       - recent activity log
//
// The rest of the program (main.cpp) only talks to this class, which keeps the
// list and the tree consistent with each other.
#pragma once

#include <string>
#include <vector>

#include "ActivityQueue.h"
#include "Contact.h"
#include "ContactList.h"
#include "PhoneBST.h"
#include "UndoStack.h"

using namespace std;

class ContactBook {
public:
    // ---- Core operations required by the assignment ----

    // Add a contact. Fails (with a message in `error`) if the number exists.
    bool add(const Contact& contact, string& error);

    // Delete a contact that was found with one of the search functions.
    bool remove(ContactNode* node);

    // Replace the data of an existing contact. The list position is recomputed
    // because the name may have changed.
    bool update(ContactNode* node, const Contact& updated, string& error);

    // Search by mobile number (exact, normalized). Uses the BST.
    ContactNode* findByPhone(const string& phone) const;

    // Search by name (partial, case-insensitive). Uses the linked list.
    vector<ContactNode*> findByName(const string& keyword) const;

    // Number of contacts. O(1) because the list tracks its size.
    int count() const { return list_.size(); }

    // First node of the sorted list (iterate with ->next).
    ContactNode* first() const { return list_.first(); }

    // ---- Extras ----

    bool canUndo() const { return !undo_.empty(); }
    bool undo(string& message);
    vector<string> recentActivity() const { return activity_.snapshot(); }

    // ---- File I/O (one contact per line: name|phone|email) ----

    // Loads contacts without recording undo/activity entries.
    // Returns the number loaded; `skipped` counts invalid or duplicate lines.
    int loadFromFile(const string& path, int& skipped);

    // Writes to a temporary file first, then replaces the real file.
    bool saveToFile(const string& path) const;

private:
    ContactList list_;
    PhoneBST index_;
    UndoStack undo_;
    ActivityQueue activity_;

    // Insert/remove in list + tree together, without undo or logging.
    bool insertRaw(const Contact& contact);
    bool removeRaw(const string& phone);

    void log(const string& message);
};
