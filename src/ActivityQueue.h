// ActivityQueue.h
// DATA STRUCTURE 4: Queue (FIFO), implemented as a circular array.
//
// Keeps the last CAPACITY activity messages (for example "Added Abel"). When the
// queue is full the oldest message is dequeued to make room for the new one, so
// the history is always the most recent events in the order they happened.
// enqueue and dequeue are O(1); the fixed-size array also covers the "arrays"
// data structure from the assignment list.
#pragma once

#include <string>
#include <vector>

using namespace std;

class ActivityQueue {
public:
    static const int CAPACITY = 10;

    ActivityQueue() : head_(0), count_(0) {}

    void enqueue(const string& message) {
        if (count_ == CAPACITY) {
            string dropped;
            dequeue(dropped);  // make room by discarding the oldest entry
        }
        items_[(head_ + count_) % CAPACITY] = message;
        ++count_;
    }

    bool dequeue(string& out) {
        if (count_ == 0) return false;
        out = items_[head_];
        head_ = (head_ + 1) % CAPACITY;
        --count_;
        return true;
    }

    // Oldest first, without removing anything.
    vector<string> snapshot() const {
        vector<string> result;
        for (int i = 0; i < count_; ++i) {
            result.push_back(items_[(head_ + i) % CAPACITY]);
        }
        return result;
    }

    bool empty() const { return count_ == 0; }
    int size() const { return count_; }

private:
    string items_[CAPACITY];
    int head_;   // index of the oldest element
    int count_;  // number of stored elements
};
