// ContactList.cpp
#include "ContactList.h"

#include "Validation.h"

using namespace std;

// Ordering rule for the sorted list: name (case-insensitive), then phone.
static bool comesBefore(const Contact& a, const Contact& b) {
    string nameA = validation::toLower(a.name);
    string nameB = validation::toLower(b.name);
    if (nameA != nameB) return nameA < nameB;
    return a.phone < b.phone;
}

ContactList::ContactList() : head_(nullptr), size_(0) {}

ContactList::~ContactList() {
    while (head_ != nullptr) {
        ContactNode* next = head_->next;
        delete head_;
        head_ = next;
    }
}

ContactNode* ContactList::insertSorted(const Contact& contact) {
    ContactNode* node = new ContactNode{contact, nullptr};

    if (head_ == nullptr || comesBefore(contact, head_->data)) {
        // New first element (also covers the empty list).
        node->next = head_;
        head_ = node;
    } else {
        // Walk until the next node should come after the new one.
        ContactNode* current = head_;
        while (current->next != nullptr && !comesBefore(contact, current->next->data)) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }

    ++size_;
    return node;
}

bool ContactList::removeNode(ContactNode* node) {
    if (node == nullptr || head_ == nullptr) return false;

    if (head_ == node) {
        head_ = node->next;
    } else {
        ContactNode* previous = head_;
        while (previous->next != nullptr && previous->next != node) {
            previous = previous->next;
        }
        if (previous->next == nullptr) return false;  // node is not in this list
        previous->next = node->next;
    }

    delete node;
    --size_;
    return true;
}

vector<ContactNode*> ContactList::searchByName(const string& keyword) const {
    vector<ContactNode*> matches;
    string needle = validation::toLower(keyword);

    for (ContactNode* current = head_; current != nullptr; current = current->next) {
        if (validation::toLower(current->data.name).find(needle) != string::npos) {
            matches.push_back(current);
        }
    }
    return matches;
}
