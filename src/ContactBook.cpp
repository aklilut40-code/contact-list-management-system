// ContactBook.cpp
#include "ContactBook.h"

#include <ctime>
#include <filesystem>
#include <fstream>

#include "Validation.h"

using namespace std;

namespace {

string timestamp() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    char buffer[16];
    if (local != nullptr && strftime(buffer, sizeof(buffer), "%H:%M:%S", local) > 0) {
        return buffer;
    }
    return "--:--:--";
}

}  // namespace

void ContactBook::log(const string& message) {
    activity_.enqueue("[" + timestamp() + "] " + message);
}

bool ContactBook::insertRaw(const Contact& contact) {
    if (index_.find(contact.phone) != nullptr) return false;
    ContactNode* node = list_.insertSorted(contact);
    index_.insert(contact.phone, node);
    return true;
}

bool ContactBook::removeRaw(const string& phone) {
    ContactNode* node = index_.find(phone);
    if (node == nullptr) return false;
    index_.remove(phone);   // tree first: `phone` may point into the node
    list_.removeNode(node);
    return true;
}

bool ContactBook::add(const Contact& contact, string& error) {
    ContactNode* existing = index_.find(contact.phone);
    if (existing != nullptr) {
        error = "That number already belongs to " + existing->data.name + ".";
        return false;
    }

    insertRaw(contact);

    Action action;
    action.type = Action::ADD;
    action.after = contact;
    undo_.push(action);

    log("Added " + contact.name);
    return true;
}

bool ContactBook::remove(ContactNode* node) {
    if (node == nullptr) return false;

    Contact removed = node->data;  // copy before the node is freed
    if (!removeRaw(removed.phone)) return false;

    Action action;
    action.type = Action::REMOVE;
    action.before = removed;
    undo_.push(action);

    log("Deleted " + removed.name);
    return true;
}

bool ContactBook::update(ContactNode* node, const Contact& updated, string& error) {
    if (node == nullptr) {
        error = "No contact selected.";
        return false;
    }

    Contact old = node->data;  // copy before the node is freed

    if (updated.phone != old.phone) {
        ContactNode* clash = index_.find(updated.phone);
        if (clash != nullptr) {
            error = "That number already belongs to " + clash->data.name + ".";
            return false;
        }
    }

    removeRaw(old.phone);
    insertRaw(updated);

    Action action;
    action.type = Action::UPDATE;
    action.before = old;
    action.after = updated;
    undo_.push(action);

    log("Updated " + old.name);
    return true;
}

ContactNode* ContactBook::findByPhone(const string& phone) const {
    return index_.find(phone);
}

vector<ContactNode*> ContactBook::findByName(const string& keyword) const {
    return list_.searchByName(keyword);
}

bool ContactBook::undo(string& message) {
    Action action;
    if (!undo_.pop(action)) {
        message = "Nothing to undo.";
        return false;
    }

    switch (action.type) {
        case Action::ADD:
            removeRaw(action.after.phone);
            message = "Removed " + action.after.name + " (undo of add).";
            break;
        case Action::REMOVE:
            insertRaw(action.before);
            message = "Restored " + action.before.name + " (undo of delete).";
            break;
        case Action::UPDATE:
            removeRaw(action.after.phone);
            insertRaw(action.before);
            message = "Reverted changes to " + action.before.name + " (undo of update).";
            break;
    }

    log("Undo: " + message);
    return true;
}

int ContactBook::loadFromFile(const string& path, int& skipped) {
    skipped = 0;
    ifstream in(path);
    if (!in) return 0;  // first run: no file yet, start with an empty book

    int loaded = 0;
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();  // Windows line endings
        if (validation::trim(line).empty()) continue;

        // Expected format: name|phone|email  (email may be empty)
        size_t first = line.find('|');
        size_t second = (first == string::npos) ? string::npos : line.find('|', first + 1);
        if (first == string::npos || second == string::npos) {
            ++skipped;
            continue;
        }

        Contact contact;
        contact.name = validation::trim(line.substr(0, first));
        string rawPhone = line.substr(first + 1, second - first - 1);
        contact.email = validation::trim(line.substr(second + 1));

        string error;
        if (!validation::validName(contact.name, error) ||
            !validation::normalizePhone(rawPhone, contact.phone, error) ||
            !validation::validEmail(contact.email, error) || !insertRaw(contact)) {
            ++skipped;
            continue;
        }
        ++loaded;
    }
    return loaded;
}

bool ContactBook::saveToFile(const string& path) const {
    const string tempPath = path + ".tmp";

    {
        ofstream out(tempPath, ios::trunc);
        if (!out) return false;

        for (ContactNode* node = list_.first(); node != nullptr; node = node->next) {
            out << node->data.name << '|' << node->data.phone << '|' << node->data.email << '\n';
        }
        out.flush();
        if (!out) return false;
    }

    // Replace the old file only after the new one was written completely.
    error_code ec;
    filesystem::rename(tempPath, path, ec);
    if (ec) {
        filesystem::remove(tempPath, ec);
        return false;
    }
    return true;
}
