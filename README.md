### Overview and Features

## 📁 Files and Directory Structure

The project is organized into modular directories, each responsible for a specific part of the system:

- **`binary_files/`** – Manages binary file I/O using `file_record` and utility helpers.
- **`bplustree/`** – Contains the implementation of B+ Tree algorithms and data structures.
- **`linked_list_functions/`** – Provides utility functions for linked list operations.
- **`node/`** – Includes node classes used in various data structures.
- **`parser/`** – Parses SQL-like commands and builds internal representations.
- **`queue/`** – Implements queue data structures and supporting functions.
- **`shunting_yard/`** – Implements the Shunting Yard algorithm for expression parsing.
- **`sql/`** – Core SQL logic including data structure and command execution.
- **`stack/`** – Implements stack data structures and operations.
- **`table/`** – Manages table creation, storage, and data access.
- **`token/`** – Defines classes for token objects used in parsing.
- **`tokenizer/`** – Implements a tokenizer using state machine techniques.

---

##  Features

- **SQL-like Commands** – Supports commands such as `make table`, `insert into`, and `select`.
- **Table Management** – Allows creation of tables with user-defined fields.
- **Data Insertion** – Supports inserting rows of data into defined tables.
- **Select Queries** – Executes `SELECT` queries with filters and logical conditions.
- **Tokenization** – Breaks down input SQL commands into tokens for parsing.
- **File Handling** – Reads/writes binary files using custom file access classes.

## 🛠 Configuration and Build Instructions

### Build and Run:

> 💡 **Note:** It is **highly recommended** to run this project using **Visual Studio Code (VSCode)** with the **CMake** and **CMake Tools** extensions installed.  
> 💡 **Compiler Tip:** When prompted during reconfiguration, select **Clang** (or a similar compiler) for best compatibility.



1. Right-click `CMakeLists.txt` → `Clean Reconfigure All Projects`
<img src="src/Screenshot 2025-03-30 at 4.46.02 PM.png" alt="Setup Screenshot" width="50%" />
<img src="src/Screenshot 2025-03-30 at 4.46.16 PM.png" alt="Setup Screenshot" width="50%" />

2. Click the **Play (▶️)** button on the bottom bar
<img src="src/Screenshot 2025-03-30 at 4.48.59 PM.png" alt="Setup Screenshot" />

3. Select `testB` to run your tests
<img src="src/Screenshot 2025-03-30 at 4.49.43 PM.png" alt="Setup Screenshot" />

## 💬  Quick Tutorial

This program accepts simplified SQL-like commands through an interactive interface. Below are the supported commands and examples:

### 📌 1. Create a Table
```sql
make table employee fields last, first, dep, salary, year
```
### 📌 2. Insert Records
```
insert into employee values Blow,Joe,CS,100000,2018
insert into employee values "Billy", Jackson, Math, 27000, 2022
```
### 📌 3. Select All Records
```
select * from employee
```
### 📌 4. Select Specific Fields
```
select * from employee where last = Blow
select * from employee where (dep=CS or salary=100000)
```

### Demo
<img src="src/Screenshot 2025-03-30 at 5.16.48 PM.png" alt="Setup Screenshot" />

<img src="src/Screenshot 2025-03-30 at 5.17.29 PM.png" alt="Setup Screenshot" />

<img src="src/Screenshot 2025-03-30 at 5.17.53 PM.png" alt="Setup Screenshot" />

<img src="src/Screenshot 2025-03-30 at 5.18.32 PM.png" alt="Setup Screenshot" />

<img src="src/Screenshot 2025-03-30 at 5.19.14 PM.png" alt="Setup Screenshot" />

<img src="src/Screenshot 2025-03-30 at 5.20.21 PM.png" alt="Setup Screenshot" />
