# Mobile Contact List Management System

A console application written in **C++17** that manages a mobile phone contact list.
Made for the **Data Structures assignment**, Mekelle University, School of Computing,
Software Engineering Department.

- **Chosen system:** K. Mobile Contact List Management System
- **Section / Group:** Section 2, Group 6

---

## Table of contents

1. [What the program does](#1-what-the-program-does)
2. [Files in the project (read in this order)](#2-files-in-the-project-read-in-this-order)
3. [How to run it](#3-how-to-run-it)
4. [How to use the menu](#4-how-to-use-the-menu)
5. [Data structures: purpose, steps and why](#5-data-structures-purpose-steps-and-why)
6. [Function reference](#6-function-reference)
7. [Data file format](#7-data-file-format)
8. [Input validation and error handling](#8-input-validation-and-error-handling)
9. [Testing](#9-testing)
10. [Known limitations](#10-known-limitations)

---

## 1. What the program does

You can store people's names, mobile numbers and optional emails and manage them from a menu.

| Menu | Operation | Data structure used |
|---|---|---|
| 1 | Add a contact (inserted in alphabetical position) | Sorted singly linked list |
| 2 | Delete a contact | Linked list + BST |
| 3 | Update a contact | Linked list + BST |
| 4 | Search by name (partial, ignores upper/lower case) | Linked list |
| 5 | Search by mobile number | Binary search tree |
| 6 | Display all contacts, sorted by name | Linked list |
| 7 | Count contacts | Counter in the linked list (O(1)) |
| 8 | Undo the last change (extra) | Stack |
| 9 | Show recent activity (extra) | Queue (circular array) |
| 0 | Save and exit | File I/O |

Four data structures are used (the assignment requires at least three):
**linked list, binary search tree, stack, queue (built on an array).**

---

## 2. Files in the project (read in this order)

Start at the top. Each file only depends on the ones above it.

| # | File | Purpose |
|---|---|---|
| 1 | `src/Contact.h` | The `Contact` record: name, phone, email. |
| 2 | `src/Validation.h` / `.cpp` | Checks input (name, phone, email) and cleans phone numbers. |
| 3 | `src/ContactList.h` / `.cpp` | **Sorted singly linked list**: the main storage of all contacts. |
| 4 | `src/PhoneBST.h` / `.cpp` | **Binary search tree**: fast search by mobile number. |
| 5 | `src/UndoStack.h` | **Stack**: remembers changes so they can be undone. |
| 6 | `src/ActivityQueue.h` | **Queue** (circular array): remembers the last 10 actions. |
| 7 | `src/ContactBook.h` / `.cpp` | Joins everything above into one class, and does file loading/saving. |
| 8 | `src/main.cpp` | The menu and all screen input/output. |
| 9 | `data/contacts.txt` | Sample data with 10 contacts. |
| 10 | `Makefile` | Build commands (`make`, `make run`, `make test`, `make clean`). |
| 11 | `tests/run_tests.sh` | 37 automated tests. |
| 12 | `docs/REPORT.md` | Report: structure choices, complexity analysis, screenshots section. |
| 13 | `.gitignore` | Tells Git to ignore the compiled program. |
| 14 | `README.md` | This file. |

Folder layout:

```
contact-list-management-system/
├── src/
│   ├── Contact.h
│   ├── Validation.h
│   ├── Validation.cpp
│   ├── ContactList.h
│   ├── ContactList.cpp
│   ├── PhoneBST.h
│   ├── PhoneBST.cpp
│   ├── UndoStack.h
│   ├── ActivityQueue.h
│   ├── ContactBook.h
│   ├── ContactBook.cpp
│   └── main.cpp
├── data/contacts.txt
├── tests/run_tests.sh
├── docs/REPORT.md
├── Makefile
├── .gitignore
└── README.md
```

---

## 3. How to run it

You need a C++17 compiler (`g++` 8 or newer, or `clang`, or MinGW on Windows).

### Option A: with make (Linux, macOS, Windows with MinGW)

```bash
make          # compile -> creates the program "contacts"
make run      # compile and start with the sample data
make test     # run the 37 automated tests
make clean    # delete the compiled program
```

### Option B: without make (one command)

```bash
g++ -std=c++17 -O2 -o contacts src/main.cpp src/ContactList.cpp src/PhoneBST.cpp src/ContactBook.cpp src/Validation.cpp
./contacts data/contacts.txt
```

On Windows the program is `contacts.exe`, so run `contacts.exe data/contacts.txt`.

### Option C: from a phone

Open the repository on GitHub, press **Code > Codespaces > Create codespace**. You get a
terminal in the browser with `g++` and `make` already installed. Then run `make run`.

If you start the program without a file name (`./contacts`) it uses `contacts.txt` in
the current folder and creates it on exit.

---

## 4. How to use the menu

```
=========================================
   MOBILE CONTACT LIST MANAGEMENT SYSTEM
=========================================
 1. Add contact              6. Display all contacts
 2. Delete contact           7. Count contacts
 3. Update contact           8. Undo last change
 4. Search by name           9. Recent activity
 5. Search by mobile number  0. Save and exit
```

Type the number and press Enter.

- **Add:** enter name, mobile number, optional email. Leave name or number empty to cancel.
- **Delete / Update:** type a name (or part of it) or a mobile number. If several contacts match, a numbered list appears and you choose one. Delete asks `y/n` first. In Update, press Enter to keep a value, and type `-` to clear the email.
- **Search:** name search matches part of a name (`mer` finds `Meron Tadesse`). Number search needs the full number.
- **Undo:** reverses the newest change first (add, delete or update), and can be repeated.
- **Mobile numbers** can be typed as `0911000101`, `251911000101` or `+251 911 000 101`; all are stored as `+251911000101`.
- Every change is saved to the file immediately.

---

## 5. Data structures: purpose, steps and why

How they fit together:

```
          +------------------------------ ContactBook ------------------------------+
          |                                                                          |
 add ---> |  ContactList (sorted linked list)    PhoneBST (index by phone)           |
 delete   |  Abel -> Beth -> Dawit -> ...   <----  pointers to the list nodes        |
 update   |                                                                          |
          |  UndoStack (LIFO)   push on every change, pop on "undo"                  |
          |  ActivityQueue (FIFO, 10)   oldest entry dropped when full               |
          +--------------------------------------------------------------------------+
```

The linked list owns the contact data. The tree stores only pointers to list nodes, so
nothing is stored twice and nothing can get out of sync. `ContactBook` always updates both.

### 5.1 Sorted singly linked list (`ContactList`)

**Purpose:** main storage. Contacts are always kept in alphabetical order, so displaying
needs no sorting. The assignment asks for a sorted linked list for "Add Contact".

**Shape:** `head -> [Abel] -> [Beth] -> [Dawit] -> null`. Each node holds one `Contact` and
a `next` pointer.

**Insert steps (`insertSorted`):**
1. Create a new node.
2. If the list is empty, or the new contact comes before the first one, make it the new head.
3. Otherwise walk forward until the next node should come after the new contact.
4. Link the new node in: `new->next = current->next; current->next = new`.
5. Increase the size counter.

**Remove steps (`removeNode`):**
1. If the node is the head, move `head` to `node->next`.
2. Otherwise walk to the node just before it and set `previous->next = node->next`.
3. Delete the node, decrease the size counter.

**Why a list and not an array?** Inserting in the middle of a sorted array shifts every later
element and the size must be fixed in advance. A list only changes two pointers and grows
one node at a time.

### 5.2 Binary search tree (`PhoneBST`)

**Purpose:** find a contact by mobile number without scanning the whole list.

**Rule:** for every node, all keys in the left subtree are smaller and all keys in the right
subtree are larger. The key is the phone number; the value is a pointer to the list node.

**Search steps (`find`):** start at the root; if the key is equal, done; if smaller go left;
if larger go right; if you reach nothing, it does not exist.

**Insert steps (`insert`):** follow the same path as a search; when you reach an empty spot
put the new node there. If the key is already in the tree, the insert fails. This is how
duplicate numbers are blocked.

**Delete steps (`remove`):** three cases.
1. Leaf: just delete it.
2. One child: replace the node with that child.
3. Two children: copy the in-order successor (smallest key in the right subtree) into the node, then delete that successor.

### 5.3 Stack (`UndoStack`)

**Purpose:** undo. Last in, first out (LIFO): the most recent change is undone first.

**Steps:**
1. After every successful add, delete or update, push an `Action` (type plus the contact before and/or after).
2. On "Undo", pop the top action and do the opposite:

| Popped action | What undo does |
|---|---|
| ADD | remove the added contact |
| REMOVE | insert the deleted contact again |
| UPDATE | remove the new version, insert the old version |

Built from linked nodes, so there is no size limit. `push` and `pop` are O(1).

### 5.4 Queue on a circular array (`ActivityQueue`)

**Purpose:** a log of the last 10 actions (first in, first out, FIFO).

**Steps:**
1. A fixed array of 10 strings with two numbers: `head` (index of the oldest) and `count`.
2. `enqueue`: write at index `(head + count) % 10`, then `count++`.
3. If the array is full, first `dequeue` the oldest (`head = (head + 1) % 10`, `count--`).
4. The `% 10` makes the index wrap around to the start, which is what "circular" means.

---

## 6. Function reference

### `Validation.cpp`

| Function | What it does |
|---|---|
| `trim(s)` | Removes spaces at the start and end. |
| `toLower(s)` | Returns the text in lower case (for case-insensitive compare). |
| `validName(name, error)` | Name must be 1 to 40 characters, no `\|`, no control characters. |
| `normalizePhone(input, out, error)` | Removes spaces/dashes/brackets, converts `09..`/`07..` and `251..` to `+251..`, requires 7 to 15 digits. |
| `validEmail(email, error)` | Empty is fine; otherwise must look like `name@domain.com`. |
| `looksLikePhone(s)` | True if the text has a digit and no letters (decides name vs number). |

### `ContactList.cpp` (sorted linked list)

| Function | What it does | Time |
|---|---|---|
| `insertSorted(contact)` | Inserts at the correct alphabetical position, returns the new node. | O(n) |
| `removeNode(node)` | Unlinks and frees a node. | O(n) |
| `searchByName(keyword)` | Returns every contact whose name contains the keyword. | O(n) |
| `first()` / `size()` | First node (to loop through the list) / number of contacts. | O(1) |
| `comesBefore(a, b)` | Ordering rule: name first (ignoring case), then phone. | O(m) |
| destructor | Frees all nodes. | O(n) |

### `PhoneBST.cpp` (binary search tree)

| Function | What it does | Time |
|---|---|---|
| `insert(key, node)` | Adds a number; returns false if it already exists. | O(h) |
| `find(key)` | Returns the list node for a number, or nothing. | O(h) |
| `remove(key)` | Deletes a number (3 cases above). | O(h) |
| `removeRecursive` | Helper used by `remove`. | O(h) |
| `destroy` | Frees the whole tree (destructor helper). | O(n) |

### `UndoStack.h`

| Function | What it does | Time |
|---|---|---|
| `push(action)` | Puts an action on top. | O(1) |
| `pop(action)` | Takes the newest action off; returns false if empty. | O(1) |
| `empty()` / `size()` | Is it empty / how many actions. | O(1) |

### `ActivityQueue.h`

| Function | What it does | Time |
|---|---|---|
| `enqueue(message)` | Adds at the back; drops the oldest if full. | O(1) |
| `dequeue(out)` | Removes and returns the oldest message. | O(1) |
| `snapshot()` | Copy of all messages, oldest first. | O(10) |
| `empty()` / `size()` | Is it empty / how many messages. | O(1) |

### `ContactBook.cpp` (the class `main.cpp` uses)

| Function | What it does |
|---|---|
| `add(contact, error)` | Rejects duplicate numbers; inserts into list and tree; pushes undo; logs. |
| `remove(node)` | Removes from tree and list; pushes undo; logs. |
| `update(node, updated, error)` | Checks the new number is free; removes old, inserts new (name may move position); pushes undo; logs. |
| `findByPhone(phone)` | BST lookup. |
| `findByName(keyword)` | Linked list search. |
| `count()` / `first()` | Number of contacts / start of the list. |
| `undo(message)` | Pops the stack and reverses the action. |
| `recentActivity()` | Messages from the queue. |
| `loadFromFile(path, skipped)` | Reads the file, validates each line, skips bad ones. |
| `saveToFile(path)` | Writes `path.tmp` first, then replaces the real file (safe against crashes). |
| `insertRaw` / `removeRaw` | Private: change list and tree together without touching undo or the log. |
| `log(message)` | Private: adds a time-stamped message to the queue. |

### `main.cpp` (screen input and output)

| Function | What it does |
|---|---|
| `main` | Loads the file, shows the menu in a loop, saves on exit. |
| `printMenu` | Draws the menu. |
| `readLine` | Shows a prompt and reads one trimmed line (false at end of input). |
| `askName` / `askPhone` / `askEmail` | Ask for one value and repeat until it is valid. |
| `selectContact` | Lets the user pick one contact by number or name (used by delete and update). |
| `addContact` / `deleteContact` / `updateContact` | The menu actions 1, 2, 3. |
| `searchByName` / `searchByPhone` | The menu actions 4, 5. |
| `displayAll` | Menu action 6: prints the table and the total. |
| `undoLast` / `showActivity` | Menu actions 8, 9. |
| `printTable` | Prints contacts as an aligned table. |
| `saveOrWarn` | Saves after a change and warns if saving fails. |

---

## 7. Data file format

One contact per line: `name|mobile|email`. The email may be empty.

```
Abel Tesfay|+251911000101|abel.tesfay@example.com
Dawit Gebre|+251933000303|
```

Lines that are malformed, invalid or duplicate are skipped when loading, and the program
tells you how many were skipped. If the file does not exist yet, the program starts empty.

---

## 8. Input validation and error handling

- Name: not empty, at most 40 characters, no `|`.
- Mobile number: digits only (plus an optional leading `+`), 7 to 15 digits, **no duplicates**.
- Email: optional, must look like `name@domain.com`.
- Unknown contact, invalid menu option and nothing-to-undo all give a clear message and the program keeps running.
- Delete asks for confirmation.
- Pressing Enter on an empty name or number cancels the current operation.
- End of input (Ctrl+D, or Ctrl+Z on Windows) saves and exits normally.

---

## 9. Testing

`make test` runs `tests/run_tests.sh`: 37 end-to-end tests that feed scripted input to the
real program and check the output. They cover adding, duplicates, number formats, sorted
order, both searches, delete, update, every kind of undo, the queue dropping old entries,
bad input, bad files and data surviving a restart.

---

## 10. Known limitations

- The BST does not balance itself. If numbers were inserted in strictly increasing order it would behave like a list (O(n)). Real numbers arrive in random order; an AVL tree would be the improvement.
- Name search scans the whole list (O(n)), which is fine for a personal contact list.
- Names cannot contain `|` because it is the file separator.
- The undo history grows during a session and is cleared when the program exits.

See [docs/REPORT.md](docs/REPORT.md) for the complexity analysis.
