// PhoneBST.cpp
#include "PhoneBST.h"

using namespace std;

PhoneBST::PhoneBST() : root_(nullptr), size_(0) {}

PhoneBST::~PhoneBST() { destroy(root_); }

void PhoneBST::destroy(BSTNode* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool PhoneBST::insert(const string& key, ContactNode* contact) {
    // `link` points at the pointer we will eventually overwrite.
    BSTNode** link = &root_;
    while (*link != nullptr) {
        if (key == (*link)->key) return false;  // duplicate number
        link = (key < (*link)->key) ? &(*link)->left : &(*link)->right;
    }
    *link = new BSTNode{key, contact, nullptr, nullptr};
    ++size_;
    return true;
}

ContactNode* PhoneBST::find(const string& key) const {
    BSTNode* current = root_;
    while (current != nullptr) {
        if (key == current->key) return current->contact;
        current = (key < current->key) ? current->left : current->right;
    }
    return nullptr;
}

bool PhoneBST::remove(const string& key) {
    bool removed = false;
    root_ = removeRecursive(root_, key, removed);
    if (removed) --size_;
    return removed;
}

BSTNode* PhoneBST::removeRecursive(BSTNode* node, const string& key, bool& removed) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        node->left = removeRecursive(node->left, key, removed);
    } else if (key > node->key) {
        node->right = removeRecursive(node->right, key, removed);
    } else {
        removed = true;

        // Case 1 and 2: zero or one child -> replace the node by its child.
        if (node->left == nullptr) {
            BSTNode* child = node->right;
            delete node;
            return child;
        }
        if (node->right == nullptr) {
            BSTNode* child = node->left;
            delete node;
            return child;
        }

        // Case 3: two children -> copy the in-order successor (smallest key in
        // the right subtree) here, then delete that successor.
        BSTNode* successor = node->right;
        while (successor->left != nullptr) successor = successor->left;

        string successorKey = successor->key;  // copy: the node is freed below
        node->key = successorKey;
        node->contact = successor->contact;

        bool ignored = false;
        node->right = removeRecursive(node->right, successorKey, ignored);
    }
    return node;
}
