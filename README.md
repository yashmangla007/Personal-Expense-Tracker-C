# Personal Expense Tracker (C Project)

A robust, console-based financial management system developed in C. This project demonstrates low-level file handling, database management concepts, and modular programming logic.

## Key Highlights and Features of Project

### 1. **Dual-Redundancy Data Backup**
   - Unlike standard projects that write to a single file, this system implements a **Real-time Backup Mechanism**.
   - Every transaction is simultaneously written to both `ExpenseRecord.txt` and `Backup-ExpenseRecord.txt`, ensuring data persistence even if the main file gets corrupted.

### 2. **Custom Database Logic (CRUD)**
   - Implements full **Create, Read, Update, and Delete** functionality without using external libraries or SQL.
   - Features a custom **ID Auto-Increment Algorithm** that scans previous records to generate unique transaction IDs automatically.

### 3. **Smart Reporting Engine**
   - Includes a filter algorithm that parses through raw text data to generate **Category-specific reports**.
   - Calculates totals dynamically, allowing users to instantly see exactly how much they spent on specific categories like "Food" or "Travel."

### 4. **Secure Session Management**
   - Features a PIN-based authentication system to protect financial data from unauthorized access upon application launch.

## Technical Concepts Used
* **File I/O:** `fopen`, `fprintf`, `fscanf`, `rewind` for persistent storage.
* **Data Structures:** Custom `struct` implementation for complex data handling.
* **Buffer Management:** Careful handling of `stdin` buffers to prevent input skipping.
* **Modular Design:** Code is split into specific functions (`addExpense`, `deleteExpense`, etc.) for maintainability.

## Project Structure
* `PET_Home.C`: The main source code.
* `PET_Home.exe`: Compiled executable (Windows).
* `Expenses/`: Directory containing database records.