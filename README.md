# 🎬 Movie Management System

A professional C++ desktop application built with the **Qt Framework**, featuring a layered architecture, custom models, and full data persistence. This project was designed to manage a movie database with distinct Administrator and User modes.

## 🚀 Core Features

### 🛠 Administrator Mode
* **Database Management:** Add, update, and delete movies (Title, Genre, Year, Likes, Trailer Link).
* **Validation:** Strict data validation using custom `Validator` classes and Exception handling.
* **Undo/Redo**
* **Live Updates:** Repository changes are reflected instantly in the GUI using a custom `QAbstractTableModel`.

### 👤 User Mode
* **Interactive Discovery:** Filter movies by genre and cycle through them one by one.
* **Auto-Play Trailers:** Movie trailers open automatically in the default web browser.
* **Personal Watchlist:** Add movies to a list and "Like" them upon completion to update the global database.
* **Export Options:** Save and view the watchlist in **CSV** (Excel/Notepad) or **HTML** (Browser) formats.

---

## 🏗 Technical Specifications

### 📂 Layered Architecture
1. **Domain Layer:** `Movie` entity and `Validators`.
2. **Repository Layer:** File-backed storage using `iostream` (text files).
3. **Service Layer:** Business logic, STL algorithm integration, and Undo/Redo stacks.
4. **GUI Layer:** Custom Qt interface (manual layouts) utilizing the **Model/View** architecture.

### 💻 Performance & Standards
* **STL Integration:** Replaced all manual loops with STL algorithms (`std::copy_if`, `std::for_each`, `std::find`, etc.).
* **Memory Safety:** Smart pointers and RAII principles for resource management.
* **Testing:** **98% Code Coverage** on all non-UI layers (Service & Repository).
* **Exception Handling:** Custom exception hierarchy for repository conflicts and user input errors.
