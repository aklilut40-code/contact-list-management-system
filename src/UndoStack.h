// UndoStack.h
// DATA STRUCTURE 3: Stack (LIFO), implemented with a linked list.
//
// Every successful add / delete / update pushes an Action. "Undo" pops the most
// recent action and reverses it, so the newest change is always undone first.
// push, pop and peek are all O(1).
#pragma once

#include "Contact.h"

using namespace std;

struct Action {
    enum Type { ADD, REMOVE, UPDATE };

    Type type = ADD;
    Contact before;  // state before the change (REMOVE, UPDATE)
    Contact after;   // state after the change  (ADD, UPDATE)
};

class UndoStack {
public:
    UndoStack() : top_(nullptr), size_(0) {}
    ~UndoStack() {
        Action discarded;
        while (pop(discarded)) {
        }
    }

    UndoStack(const UndoStack&) = delete;
    UndoStack& operator=(const UndoStack&) = delete;

    void push(const Action& action) {
        top_ = new Node{action, top_};
        ++size_;
    }

    // Removes the newest action and copies it to `out`. False when empty.
    bool pop(Action& out) {
        if (top_ == nullptr) return false;
        Node* node = top_;
        out = node->action;
        top_ = node->next;
        delete node;
        --size_;
        return true;
    }

    bool empty() const { return top_ == nullptr; }
    int size() const { return size_; }

private:
    struct Node {
        Action action;
        Node* next;
    };

    Node* top_;
    int size_;
};
