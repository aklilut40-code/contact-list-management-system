<div align="center">

<img src="https://capsule-render.vercel.app/api?type=rect&color=0:0F172A,50:1D4ED8,100:06B6D4&height=220&section=header&text=CONTACT%20MANAGEMENT%20SYSTEM&fontSize=32&fontColor=FFFFFF&fontAlignY=42&desc=C%2B%2B17%20%7C%20DATA%20STRUCTURES%20%7C%20CONSOLE%20APPLICATION&descSize=13&descAlignY=65&descColor=E0F2FE" width="100%" alt="Mobile Contact List Management System Banner" />

<br/>

<img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++17"/>
<img src="https://img.shields.io/badge/Data%20Structures-Implementation-2563EB?style=for-the-badge" alt="Data Structures"/>
<img src="https://img.shields.io/badge/University-Mekelle-0891B2?style=for-the-badge" alt="Mekelle University"/>

<br/><br/>

**ACADEMIC PROJECT · SOFTWARE ENGINEERING**

*Designed to demonstrate practical applications of fundamental data structures.*

</div>

---
# Mobile Contact List Management System

**Course:** Data Structures Assignment, Mekelle University, School of Computing, Software Engineering Department
**Chosen system:** K. Mobile Contact List Management System
**Section / Group:** Section 2, Group 6
**Language:** C++17 (console application)
**Due date:** May 30, 2025

## 1. Group members

| # | Full name | ID |
|---|---|---|
| 1 | _fill in_ | _fill in_ |
| 2 | _fill in_ | _fill in_ |
| 3 | _fill in_ | _fill in_ |
| 4 | _fill in_ | _fill in_ |
| 5 | _fill in_ | _fill in_ |

## 2. Introduction

The program manages a mobile phone contact list from the console. A user can add,
delete, update and search contacts, count them, display them in alphabetical order,
undo recent changes and review recent activity. Contacts are stored in a text file
so they survive between runs.

## 3. Data structures used

The assignment requires at least three different data structures. This project uses
**four**: a linked list, a binary search tree, a stack and a queue (the queue is
implemented on top of a fixed-size array).

### 3.1 Sorted singly linked list: main storage

**Where:** `ContactList.h/.cpp`. **Required by the assignment** ("Add Contact: use Sorted Linked List").

Every contact is a node. A new contact is inserted at the position that keeps the list
ordered by name (case-insensitive; equal names are ordered by number). Because the
list is always sorted:

- displaying all contacts is one pass with no sorting step,
- the output is alphabetical at all times.

**Why a linked list and not an array?** Inserting or deleting in the middle of a sorted
array moves every later element, and the array size has to be chosen in advance. A linked
list inserts by changing two pointers once the position is found and grows one node at a
time with no wasted space. A singly linked list was chosen over a doubly linked one
because one pointer per node is enough here and it uses less memory.

### 3.2 Binary search tree: index by mobile number

**Where:** `PhoneBST.h/.cpp`.

Searching a linked list by number needs a scan of every node. The tree stores each
number as a key together with a pointer to the matching list node. Looking up a number
then takes O(log n) on average. The tree holds only pointers, not copies of the
contacts, so the data lives in one place only.

The tree also enforces the **no duplicate numbers** rule: inserting an existing key fails.
Deletion handles all three cases (leaf, one child, two children using the in-order
successor).

### 3.3 Stack: undo

**Where:** `UndoStack.h`. Implemented as a linked stack.

Each successful add, delete or update pushes an `Action` that stores the contact before
and/or after the change. "Undo last change" pops the newest action and reverses it. A
stack is the natural fit because the most recent change must be undone first (LIFO).

| Undone action | Reverse operation |
|---|---|
| Add | remove the added contact |
| Delete | insert the deleted contact again |
| Update | remove the new version, insert the old version |

### 3.4 Queue (circular array): recent activity log

**Where:** `ActivityQueue.h`.

Stores the last 10 activity messages (for example `[22:41:05] Added Abel`) in a fixed
array used as a circular buffer. New messages are enqueued at the back. When the queue
is full, the oldest message is dequeued first (FIFO), so the log always shows the most
recent events in the order they happened. Using an array with wrap-around indexes gives
O(1) enqueue and dequeue with no memory allocation.

### 3.5 How they work together

`ContactBook` is the only class `main.cpp` talks to. It keeps the list and the tree
consistent: every insert or delete touches both, and the undo stack and activity queue
are updated by the same operations.

## 4. Operations and efficiency

n = number of contacts, h = height of the BST (about log n on average, up to n in the worst case),
m = length of a name, k = number of actions on the undo stack.

| Operation | Steps | Time | Reason |
|---|---|---|---|
| Add contact | duplicate check in BST, sorted insert in list, insert in BST, push undo | **O(n)** | Finding the sorted position in a singly linked list needs a walk. The BST work is O(h), the push is O(1). |
| Delete contact | find in BST, unlink from list, remove from BST, push undo | **O(n)** | A singly linked list must find the previous node. |
| Update contact | duplicate check, delete + insert, push undo | **O(n)** | Name may change, so the node moves to a new sorted position. |
| Search by name | scan list, case-insensitive substring match | **O(n · m)** | Partial matches cannot use the tree. For short names this is effectively O(n). |
| Search by mobile number | BST lookup | **O(h)**, O(log n) average | Binary search tree. |
| Count contacts | read the stored counter | **O(1)** | The list updates its size on every insert and remove. |
| Display all | one pass over the sorted list | **O(n)** | Already sorted, no sorting needed. |
| Undo | pop (O(1)) + one add or delete | **O(n)** | Dominated by the list operation. |
| Activity log enqueue/dequeue | circular array index math | **O(1)** | |
| Load from file | n inserts | **O(n²)** worst case | Each insert is O(n). Fast enough for contact lists; a file saved in sorted order can be loaded in O(n) with a tail pointer if ever needed. |
| Save to file | one pass | **O(n)** | |

### Space complexity

| Structure | Space |
|---|---|
| Linked list | O(n), one node per contact |
| BST | O(n), one tree node (key + pointer) per contact |
| Undo stack | O(k), one node per action in the session |
| Activity queue | O(1), fixed 10 entries |
| **Total** | **O(n + k)** |

### Trade-off: the BST

The index costs extra memory (one tree node per contact) and a little work on every add
and delete, but it turns the number search from O(n) into O(log n) on average. A weakness
is that this BST is not self-balancing: numbers inserted in strictly sorted order would
make it behave like a list. Contacts normally arrive in arbitrary number order, and an AVL
tree is the natural upgrade.

## 5. Error handling

| Case | Behaviour |
|---|---|
| Empty name | rejected with a message and a new prompt (empty on the first prompt cancels) |
| Name longer than 40 characters, or containing `\|` or control characters | rejected |
| Number with letters, or fewer than 7 / more than 15 digits | rejected |
| Duplicate number (on add or update) | rejected, tells which contact owns it |
| Number typed as `0911000101`, `251911000101` or `+251 911 000 101` | normalized to `+251911000101` |
| Invalid email | rejected (email is optional) |
| Contact not found when searching, deleting or updating | clear message, nothing changes |
| Several contacts match a name | numbered list, user chooses one |
| Delete | asks for confirmation (y/n) |
| Invalid menu option | message, menu shown again |
| Missing data file on first start | starts with an empty list |
| Malformed, invalid or duplicate line in the file | skipped, count is reported |
| Save failure | warning shown, program keeps running |
| End of input (Ctrl+D / Ctrl+Z) | saves and exits normally |

## 6. File I/O

Contacts are stored in a plain text file, one per line: `name|mobile|email`
(default `contacts.txt`, or the path given as the first command line argument).

- Loaded when the program starts.
- Saved after every successful add, delete, update and undo, and again on exit.
- The save writes `file.tmp` first and replaces the original only when the write
  succeeded, so a failure in the middle cannot corrupt the existing file.

## 7. Testing

`make test` runs 37 automated end-to-end tests (`tests/run_tests.sh`). They send
scripted input to the real program and check its output. They cover adding with
valid and invalid input, duplicate detection, number normalization, sorted order,
both searches, deleting by name and number, update, undo of every action type including
the LIFO order, the activity queue dropping its oldest entries, invalid menu input, loading
bad files, and data surviving a restart.

The program was also compiled with AddressSanitizer and UndefinedBehaviorSanitizer and
run through a stress sequence (300 adds, 150 deletes, 50 updates, 80 undos) with no errors and
no memory leaks.

## 8. Screenshots of program execution

> Run `make run` and replace each placeholder with a screenshot from your own run.

1. Main menu and "Loaded 10 contact(s)" message: _insert screenshot_
2. Adding a contact: _insert screenshot_
3. Rejected duplicate number and invalid input: _insert screenshot_
4. Search by name and by mobile number: _insert screenshot_
5. Display all contacts in sorted order and the contact count: _insert screenshot_
6. Update and delete (with confirmation): _insert screenshot_
7. Undo and recent activity: _insert screenshot_

## 9. Conclusion

The system covers every required operation (add, delete, update, search by name or number,
count) using a sorted linked list as the main structure, and adds a BST index, a stack and
a queue where each fits its job. Possible improvements are a self-balancing tree, a tail pointer
to make bulk loading O(n), and a limit on the undo history.
---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=rect&color=0:06B6D4,50:1D4ED8,100:0F172A&height=4&section=footer" width="100%" alt=""/>

### BUILT WITH C++17

**Mekelle University · School of Computing**  
Software Engineering Department

*Data Structures Assignment · Section 2, Group 6*

<br/>

<sub>Mobile Contact List Management System</sub>

</div>
