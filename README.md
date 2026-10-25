📱 Mobile Contact List Management System

<p align="center">
  <strong>A C++17 Console Application for Efficient Contact Management</strong>
  <br />
  Built as a Data Structures assignment at Mekelle University.
</p><p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++17" />
  <img src="https://img.shields.io/badge/Project-Data%20Structures-0D9488?style=for-the-badge" alt="Data Structures" />
  <img src="https://img.shields.io/badge/Interface-Console-334155?style=for-the-badge" alt="Console application" />
  <img src="https://img.shields.io/badge/University-Mekelle%20University-65A30D?style=for-the-badge" alt="Mekelle University" />
</p>---

📖 About the Project

The Mobile Contact List Management System is a C++17 console application designed to organize and manage mobile phone contacts through a menu-driven interface.

Developed for a Data Structures assignment in the School of Computing, Software Engineering Department at Mekelle University, this project applies fundamental programming and data structure concepts to a practical contact-management problem.

The system is intended to demonstrate how contacts can be organized, accessed, modified, and managed using appropriate data structures and file handling.

🎯 Project Information

Detail| Description
Project name| Mobile Contact List Management System
Selected system| K. Mobile Contact List Management System
Language| C++17
Interface| Console-based
Course| Data Structures
Institution| Mekelle University
Department| Software Engineering
Section| Section 2
Group| Group 6

✨ Key Objectives

- Organize mobile phone contact information.
- Apply data structures to a real-world programming problem.
- Practise algorithms for traversing, searching, inserting, and deleting data where implemented.
- Demonstrate file handling and persistent data storage where supported.
- Apply input validation and error handling.
- Build a structured, menu-driven C++ application.

🧩 Core Features

The system's intended contact-management operations may include:

- Add Contacts — enter new contact information.
- View Contacts — display saved contacts.
- Search Contacts — locate a contact using available search criteria.
- Update Contacts — modify existing contact details.
- Delete Contacts — remove unwanted contacts.
- Save and Load Data — preserve contact information using a data file, if implemented.

«Note: The exact available operations depend on the implementation in the source code. Keep only the features that your program actually supports.»

---

🛠️ Technologies Used

- C++17 — application logic and implementation.
- Data Structures and Algorithms — organizing and processing contacts.
- File Handling — reading and writing contact data, if implemented.
- Standard C++ Library — input/output, strings, and other standard utilities.

📂 Project Structure

A typical organization for this project could look like this:

contact-list-management-system/
├── README.md
├── src/
│   └── main.cpp
├── data/
│   └── contacts.txt
└── .gitignore

Your actual file and folder names may differ. Adjust this structure to match the files in your repository.

🚀 Getting Started

Prerequisites

You need:

- A C++ compiler that supports C++17, such as GCC or Clang.
- A terminal or command-line interface.
- Git, if you want to clone the repository.

Check your compiler installation:

g++ --version

1. Clone the Repository

Replace the placeholder below with your actual GitHub repository URL.

git clone https://github.com/YOUR-USERNAME/contact-list-management-system.git
cd contact-list-management-system

2. Compile the Program

If your main source file is named "main.cpp" in the project root:

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o contact_manager

If the source file is inside "src/", compile it using:

g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o contact_manager

If your project contains multiple ".cpp" files, include all required source files in the compilation command.

3. Run the Application

On Linux or macOS:

./contact_manager

On Windows using MinGW:

contact_manager.exe

Once the program starts, follow the options displayed in the console menu.

---

🧠 Data Structures and Algorithms

An important objective of this project is to demonstrate how data structures support contact-management operations.

The exact data structure used should be documented according to your implementation.

Concept| Purpose
Linked list, if implemented| Stores contacts as connected nodes and supports traversal and insertion or deletion.
Searching algorithm| Finds a contact based on a selected field, such as name or phone number.
Traversal| Visits contacts to display or process them.
Sorting, if implemented| Arranges contacts according to a selected order.
File handling, if implemented| Stores contact data so it can be loaded again later.

Why Data Structures Matter

Choosing an appropriate data structure affects how information is stored and how operations are performed.

For example, a linked list can support insertion and deletion without shifting an entire array, although locating a particular contact usually requires traversal. The actual performance depends on the operation and the way the program is implemented.

🧭 How to Use the Application

1. Start the compiled program.
2. Read the menu options displayed in the terminal.
3. Select the desired operation.
4. Enter the requested contact information.
5. Follow the program's prompts and validation messages.
6. Return to the menu to perform another operation.
7. Exit using the menu's designated exit option.

The exact menu options and input requirements are defined by the source code.

🗃️ Data Storage

If the application stores contacts in a text file, document the following:

- The name and location of the data file.
- The fields saved for each contact.
- How contacts are loaded when the program starts.
- When changes are written to the file.
- How the program handles a missing or incorrectly formatted file.

Example only: A contact record might contain a name and phone number separated by a delimiter. The actual file format must match your implementation.

🛡️ Input Validation and Error Handling

A reliable contact-management application should handle invalid input appropriately. Depending on what is implemented, validation may include:

- Rejecting invalid menu selections.
- Detecting empty or incomplete fields.
- Validating phone-number input.
- Handling searches for contacts that do not exist.
- Handling attempts to update or delete missing contacts.
- Checking file operations for errors.

These checks help make the application more predictable and easier to use.

📚 Learning Outcomes

This project provides an opportunity to practise:

- Writing modular C++ programs.
- Applying data structures to a practical problem.
- Designing menu-driven console interfaces.
- Implementing searching and traversal algorithms.
- Working with strings and user input.
- Using file handling for data persistence.
- Testing program behavior and handling errors.
- Collaborating on an academic software project.

👥 Project Team

Section 2 — Group 6

Developed as a Data Structures assignment for the Software Engineering Department, School of Computing, Mekelle University.

Add the names of the group members here if your assignment requirements permit or require them.

🔮 Future Improvements

Possible extensions, depending on the assignment requirements, include:

- Sorting contacts alphabetically.
- Preventing duplicate phone numbers.
- Supporting additional contact fields.
- Improving phone-number validation.
- Adding more flexible search options.
- Improving data-file validation and recovery.
- Adding automated tests.
- Developing a graphical interface in a future version.

🤝 Contributing

This project was developed for an academic assignment. If collaboration or external contributions are permitted, improvements can be proposed through issues or pull requests.

📄 License

No license has been specified. If you intend to distribute this project publicly, consider adding an appropriate license after confirming the requirements of your assignment and group.

---

<p align="center">
  <strong>Learn the concepts. Build the solution. Understand every line.</strong>
  <br />
  <em>Mekelle University · Software Engineering · Data Structures</em>
</p>
