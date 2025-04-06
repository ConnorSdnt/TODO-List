//
// Created by Connor Bethel on 06/04/2025.
//

#include "Persistence.h"
#include <iostream>
#include <sqlite3.h>
#include "TaskManager.h"

// Opens the SQLite database, creating it if it doesn't exist
sqlite3* Persistence::openDatabase() {
    sqlite3* db;
    if (sqlite3_open("tasks.db", &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;  // Return nullptr if opening the database fails
    }
    return db;
}

// Creates the tasks table if it doesn't already exist
void Persistence::createTableIfNotExists(sqlite3* db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            description TEXT,
            completed BOOLEAN
        );
    )";

    char* errMessage = nullptr;
    // Execute the SQL to create the table
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMessage) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMessage << std::endl;
        sqlite3_free(errMessage);  // Free the error message to avoid memory leaks
    }
}

// Inserts a new task into the tasks table
void Persistence::insertTask(sqlite3* db, Task& task, TaskManager& manager) {

    std::string title = task.getTitle();
    std::string description = task.getDescription();
    bool completed = task.getCompleted();

    const char* insertSQL = "INSERT INTO tasks (title, description, completed) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;

    // Prepare the SQL insert statement
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
        return;  // Exit early if the statement preparation fails
    }

    // Bind the values to the prepared statement
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, completed ? 1 : 0);

    // Execute the statement and check for errors
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting task: " << sqlite3_errmsg(db) << std::endl;
    }

    // Get the generated task ID from the database
    int taskID = sqlite3_last_insert_rowid(db);  // Get the ID of the last inserted task

    sqlite3_finalize(stmt);  // Finalize the prepared statement to free resources

    // Update the task in memory with the assigned ID
    task.setID(taskID);  // Set the ID on the task

    manager.addTask(task);
}

// Loads all tasks from the database into the TaskManager
void Persistence::loadTasks(sqlite3* db, TaskManager& manager) {
    const char* selectSQL = "SELECT id, title, description, completed FROM tasks";
    sqlite3_stmt* stmt;

    // Prepare the SQL select statement
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
        return;  // Exit early if statement preparation fails
    }

    // Iterate through the result set and load tasks
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        bool completed = sqlite3_column_int(stmt, 3) == 1;

        // Add the task to the TaskManager
        Task task(id, title, description, completed);
        manager.addTask(task);
    }

    sqlite3_finalize(stmt);  // Finalize the prepared statement
}

// Updates a task's information in the database
void Persistence::updateTask(sqlite3* db, Task& task) {
    const char* updateSQL = "UPDATE tasks SET title = ?, description = ?, completed = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    // Prepare the SQL update statement
    if (sqlite3_prepare_v2(db, updateSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
        return;  // Exit early if statement preparation fails
    }

    // Bind the values to the prepared statement
    sqlite3_bind_text(stmt, 1, task.getTitle().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, task.getDescription().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, task.getCompleted() ? 1 : 0);
    sqlite3_bind_int(stmt, 4, task.getID());

    // Execute the statement and check for errors
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error updating task: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);  // Finalize the prepared statement
}

// Deletes a task from the database based on its ID
void Persistence::deleteTask(sqlite3* db, int taskID) {
    const char* deleteSQL = "DELETE FROM tasks WHERE id = ?";
    sqlite3_stmt* stmt;

    // Prepare the SQL delete statement
    if (sqlite3_prepare_v2(db, deleteSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare delete statement: " << sqlite3_errmsg(db) << std::endl;
        return;  // Exit early if statement preparation fails
    }

    // Bind the task ID to the prepared statement
    sqlite3_bind_int(stmt, 1, taskID);

    // Execute the statement and check for errors
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error deleting task: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);  // Finalize the prepared statement
}
