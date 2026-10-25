<!-- =====================================================
     MOBILE CONTACT LIST MANAGEMENT SYSTEM
     C++17 | DATA STRUCTURES | MEKELLE UNIVERSITY
     ===================================================== --><div align="center">  <img src="https://capsule-render.vercel.app/api?type=rect&height=200&color=0:0F172A,50:164E63,100:0D9488&text=MOBILE%20CONTACT%20MANAGEMENT&fontSize=31&fontColor=FFFFFF&fontAlignY=40&desc=C%2B%2B17%20%7C%20DATA%20STRUCTURES%20%7C%20SOFTWARE%20ENGINEERING&descSize=13&descAlignY=65" width="100%" alt="Mobile Contact List Management System banner" />  <br />  <p>
    <strong>A console-based application for organizing and managing mobile phone contacts.</strong>
  </p>  <p>
    <img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++17" />
    <img src="https://img.shields.io/badge/Domain-Data%20Structures-0D9488?style=for-the-badge" alt="Data Structures" />
    <img src="https://img.shields.io/badge/Interface-Console-334155?style=for-the-badge" alt="Console Application" />
    <img src="https://img.shields.io/badge/Institution-Mekelle%20University-65A30D?style=for-the-badge" alt="Mekelle University" />
  </p></div>---

📑 Table of Contents

<table>
  <tr>
    <td width="50%" valign="top">📌 Overview

1. "What the Program Does" (#1-what-the-program-does)

2. "Project Structure" (#2-project-structure)

3. "How to Run It" (#3-how-to-run-it)

4. "How to Use the Menu" (#4-how-to-use-the-menu)
   
    </td>
 <td width="50%" valign="top">

⚙️ Technical Documentation

5. "Data Structures: Purpose, Steps and Why" (#5-data-structures-purpose-steps-and-why)

6. "Function Reference" (#6-function-reference)

7. "Data File Format" (#7-data-file-format)

8. "Input Validation and Error Handling" (#8-input-validation-and-error-handling)
   
    </td>

  </tr>
</table>---

1. 📱 What the Program Does

The Mobile Contact List Management System is a console application written in C++17 that manages a mobile phone contact list.

Developed for the Data Structures assignment at Mekelle University, School of Computing, Software Engineering Department, the project applies programming and data structure concepts to a practical contact-management problem.

🎯 Project Overview

<table>
  <tr>
    <td width="35%"><strong>Project Name</strong></td>
    <td>Mobile Contact List Management System</td>
  </tr>
  <tr>
    <td><strong>Chosen System</strong></td>
    <td>K. Mobile Contact List Management System</td>
  </tr>
  <tr>
    <td><strong>Programming Language</strong></td>
    <td>C++17</td>
  </tr>
  <tr>
    <td><strong>Application Type</strong></td>
    <td>Console-based application</td>
  </tr>
  <tr>
    <td><strong>Course</strong></td>
    <td>Data Structures</td>
  </tr>
  <tr>
    <td><strong>Institution</strong></td>
    <td>Mekelle University</td>
  </tr>
  <tr>
    <td><strong>Department</strong></td>
    <td>Software Engineering</td>
  </tr>
  <tr>
    <td><strong>Section / Group</strong></td>
    <td>Section 2 / Group 6</td>
  </tr>
</table>✨ Project Objectives

- Organize mobile phone contact information.
- Apply data structures to a real-world programming problem.
- Practise algorithms for traversing, searching, inserting, and deleting data where implemented.
- Demonstrate file handling and persistent data storage where supported.
- Apply input validation and error handling.
- Build a structured, menu-driven C++ application.

«Core idea: Apply data structures and algorithms to make contact information easier to manage.»

---

2. 📂 Project Structure

The project files should be organized according to the actual source code.

Example structure:

contact-list-management-system/
│
├── README.md
├── main.cpp
├── contacts.txt
└── .gitignore

«Note: This is an illustrative structure. Adjust the filenames and folders to match your actual repository.»

🧰 Technologies Used

<table>
  <thead>
    <tr>
      <th align="left">Technology</th>
      <th align="left">Purpose</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>C++17</strong></td>
      <td>Application logic and implementation.</td>
    </tr>
    <tr>
      <td><strong>Data Structures</strong></td>
      <td>Organizing and managing contact records.</td>
    </tr>
    <tr>
      <td><strong>Algorithms</strong></td>
      <td>Processing contacts through operations such as searching and traversal.</td>
    </tr>
    <tr>
      <td><strong>File Handling</strong></td>
      <td>Reading and writing contact data, if implemented.</td>
    </tr>
    <tr>
      <td><strong>Standard C++ Library</strong></td>
      <td>Supporting input/output, strings, and other programming operations.</td>
    </tr>
  </tbody>
</table>---

3. 🚀 How to Run It

Prerequisites

Before running the application, make sure you have:

- A C++ compiler supporting C++17, such as GCC or Clang.
- A terminal or command-line interface.
- Git, if you want to clone the repository.

Check whether GCC is installed:

g++ --version

Step 1 — Clone the Repository

Replace "YOUR-USERNAME" with your GitHub username.

git clone https://github.com/YOUR-USERNAME/contact-list-management-system.git

Enter the project directory:

cd contact-list-management-system

Step 2 — Compile the Program

If "main.cpp" is located in the root directory:

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o contact_manager

If your source file is located inside a "src" directory:

g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o contact_manager

If your project contains multiple ".cpp" files, include all the required source files in the compilation command.

Step 3 — Run the Application

Linux / macOS

./contact_manager

Windows using MinGW

contact_manager.exe

Once the program starts, follow the instructions displayed in the console menu.

---

4. 🖥️ How to Use the Menu

The application uses a console-based, menu-driven interface.

General Workflow

<table>
  <thead>
    <tr>
      <th align="center">Step</th>
      <th align="left">Action</th>
      <th align="left">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="center">01</td>
      <td><strong>Launch</strong></td>
      <td>Start the compiled application.</td>
    </tr>
    <tr>
      <td align="center">02</td>
      <td><strong>Select</strong></td>
      <td>Choose an operation from the displayed menu.</td>
    </tr>
    <tr>
      <td align="center">03</td>
      <td><strong>Enter Data</strong></td>
      <td>Provide the requested contact information.</td>
    </tr>
    <tr>
      <td align="center">04</td>
      <td><strong>Process</strong></td>
      <td>Allow the program to perform the selected operation.</td>
    </tr>
    <tr>
      <td align="center">05</td>
      <td><strong>Continue</strong></td>
      <td>Return to the menu to perform another operation.</td>
    </tr>
    <tr>
      <td align="center">06</td>
      <td><strong>Exit</strong></td>
      <td>Use the menu's designated exit option.</td>
    </tr>
  </tbody>
</table>The exact menu options and input requirements depend on the implementation in the source code.

---

5. 🧠 Data Structures: Purpose, Steps and Why

An important objective of this project is to demonstrate how data structures support contact-management operations.

The data structures and algorithms documented here should match the actual implementation.

📊 Data Structure Reference

Concept| Purpose| Important Consideration
Linked list, if implemented| Stores contacts as connected nodes.| Supports traversal and can allow insertion or deletion without shifting an entire array.
Searching algorithm| Locates a contact using a selected field.| Performance depends on the algorithm and data structure.
Traversal| Visits contacts one by one.| Can be used to display or process stored contacts.
Sorting, if implemented| Arranges contacts in a chosen order.| The sorting algorithm determines its time complexity.
File handling, if implemented| Stores contact information in a file.| Supports persistence when saving and loading are implemented correctly.

🔍 Why Data Structures Matter

Choosing an appropriate data structure affects how information is stored and how operations are performed.

For example, a linked list can support insertion and deletion without shifting an entire array, although finding a particular contact usually requires traversal.

The actual performance depends on the operation, the implementation, and the data structure used.

---

6. ⚙️ Function Reference

This section documents the functions responsible for the application's operations.

For accuracy: Add the actual function names, parameters, and return types from your C++ source code rather than inventing function signatures.

Function / Component| Responsibility
Main function| Starts the application and coordinates program execution.
Menu handling| Displays options and processes user selections.
Contact insertion| Adds a new contact, if implemented.
Contact traversal| Visits or displays contacts, if implemented.
Contact searching| Searches for a matching contact, if implemented.
Contact deletion| Removes a selected contact, if implemented.
File operations| Loads or saves contact data, if implemented.
Input validation| Checks input and handles invalid values, if implemented.

«The exact function names and responsibilities should be verified against the source files.»

---

7. 🗃️ Data File Format

If the application uses a file to store contacts, document its format so that the data can be understood and maintained.

Information to Document

Item| Description
File name| The actual name of the data file.
File location| The directory where the application reads or writes the file.
Record fields| The contact information stored in each record.
Field separator| The character used to separate fields, if applicable.
Loading behavior| How the application reads saved contacts.
Saving behavior| When and how contact changes are written to the file.
Error handling| What happens if the file is missing or incorrectly formatted.

Example only: A contact record might store a name and phone number separated by a delimiter. The actual format must match the application's implementation.

---

8. 🛡️ Input Validation and Error Handling

Input validation helps prevent invalid values and unexpected program behavior.

Depending on what has been implemented, the application may validate:

<table>
  <thead>
    <tr>
      <th align="left">Validation Area</th>
      <th align="left">Purpose</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Menu selection</td>
      <td>Detects invalid menu choices.</td>
    </tr>
    <tr>
      <td>Contact fields</td>
      <td>Checks for empty or incomplete information.</td>
    </tr>
    <tr>
      <td>Phone numbers</td>
      <td>Checks whether phone-number input meets the application's rules.</td>
    </tr>
    <tr>
      <td>Searching</td>
      <td>Handles cases where a matching contact cannot be found.</td>
    </tr>
    <tr>
      <td>Updating or deleting</td>
      <td>Handles attempts to modify or remove nonexistent contacts.</td>
    </tr>
    <tr>
      <td>File operations</td>
      <td>Checks for errors while reading or writing contact data.</td>
    </tr>
  </tbody>
</table>These checks help make the application more predictable and easier to use.

---

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

🔮 Future Improvements

Possible extensions, depending on assignment requirements, include:

- Sorting contacts alphabetically.
- Preventing duplicate phone numbers.
- Supporting additional contact fields.
- Improving phone-number validation.
- Adding more flexible search options.
- Improving data-file validation and recovery.
- Adding automated tests.
- Developing a graphical interface in a future version.

👥 Project Team

<table>
  <tr>
    <td><strong>Institution</strong></td>
    <td>Mekelle University</td>
  </tr>
  <tr>
    <td><strong>School</strong></td>
    <td>School of Computing</td>
  </tr>
  <tr>
    <td><strong>Department</strong></td>
    <td>Software Engineering</td>
  </tr>
  <tr>
    <td><strong>Course</strong></td>
    <td>Data Structures</td>
  </tr>
  <tr>
    <td><strong>Section</strong></td>
    <td>Section 2</td>
  </tr>
  <tr>
    <td><strong>Group</strong></td>
    <td>Group 6</td>
  </tr>
</table>Add the group members' names here if required by your assignment.

🤝 Contributing

This project was developed for an academic assignment. If collaboration or external contributions are permitted, improvements can be proposed through issues or pull requests.

📄 License

No license has been specified. If you intend to distribute this project publicly, consider adding an appropriate license after confirming the requirements of your assignment and group.

---

<div align="center">  <h3>💡 Learn the Concepts. Build the Solution. Understand Every Line.</h3>  <p>
    <strong>Mekelle University</strong><br />
    School of Computing · Software Engineering · Data Structures
  </p>  <img src="https://capsule-render.vercel.app/api?type=rect&height=80&color=0:0F172A,50:164E63,100:0D9488&section=footer" width="100%" alt="Project footer" /></div>
