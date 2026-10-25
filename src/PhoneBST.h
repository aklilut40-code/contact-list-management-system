// PhoneBST.h
// DATA STRUCTURE 2: Binary Search Tree.
//
// Index keyed by phone number. Each tree node points at the matching node of
// the sorted linked list, so a search by mobile number takes O(log n) on
// average instead of scanning the whole list. The tree does not copy contact
// data, it only stores the pointer, so there is a single source of truth.
#pragma once

#include <string>

#include "ContactList.h"

using namespace std;

struct BSTNode {
    string key;         // normalized phone number
    ContactNode* contact;    // node in the sorted linked list
    BSTNode* left;
    BSTNode* right;
};

class PhoneBST {
public:
    PhoneBST();
    ~PhoneBST();

    PhoneBST(const PhoneBST&) = delete;
    PhoneBST& operator=(const PhoneBST&) = delete;

    // Returns false if the key already exists (phone numbers are unique).
    bool insert(const string& key, ContactNode* contact);

    // Returns the list node for `key`, or nullptr when not found.
    ContactNode* find(const string& key) const;

    // Returns false when the key is not in the tree.
    bool remove(const string& key);

    int size() const { return size_; }

private:
    BSTNode* root_;
    int size_;

    static BSTNode* removeRecursive(BSTNode* node, const string& key, bool& removed);
    static void destroy(BSTNode* node);
};
