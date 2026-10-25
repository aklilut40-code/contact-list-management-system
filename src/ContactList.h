// ContactList.h
// DATA STRUCTURE 1: Sorted singly linked list.
//
// This is the main storage of the application (assignment requirement:
// "Add Contact - use Sorted Linked List"). Nodes are always kept ordered by
// name (case-insensitive, ties broken by phone number), so displaying the list
// is a single pass and needs no extra sorting step.
#pragma once

#include <string>
#include <vector>

#include "Contact.h"

using namespace std;

struct ContactNode {
    Contact data;
    ContactNode* next;
};

class ContactList {
public:
    ContactList();
    ~ContactList();

    // The list owns raw nodes, so copying is disabled to avoid double frees.
    ContactList(const ContactList&) = delete;
    ContactList& operator=(const ContactList&) = delete;

    // Insert at the position that keeps the list sorted. O(n).
    // Returns the newly created node.
    ContactNode* insertSorted(const Contact& contact);

    // Unlink and free a node that belongs to this list. O(n) because a
    // singly linked list must find the previous node.
    bool removeNode(ContactNode* node);

    // Every contact whose name contains `keyword` (case-insensitive). O(n).
    vector<ContactNode*> searchByName(const string& keyword) const;

    ContactNode* first() const { return head_; }
    int size() const { return size_; }

private:
    ContactNode* head_;
    int size_;
};
