//
// Created by Connor Bethel on 06/04/2025.
//

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <sqlite3.h>
#include "TaskManager.h"

class Persistence {
public:
    // Opens the SQLite database, creating it if it doesn't exist
    static sqlite3* openDatabase();

    // Creates the tasks table if it doesn't already exist
    static void createTableIfNotExists(sqlite3* db);

    // Inserts a new task into the tasks table
    static void insertTask(sqlite3* db, Task& task, TaskManager& manager);

    // Loads all tasks from the database into the TaskManager
    static void loadTasks(sqlite3* db, TaskManager& manager);

    static void updateTask(sqlite3* db, Task& task);

    static void deleteTask(sqlite3* db, int taskID);
};

#endif  // PERSISTENCE_H
