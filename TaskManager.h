//
// Created by Connor Bethel on 05/04/2025.
//

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <sqlite3.h>
#include <unordered_map>
#include "Task.h"

class TaskManager {
private:
    std::unordered_map<int, Task> tasks;
public:
    TaskManager() = default;

    void createTask(sqlite3* db);

    void addTask(Task& task);

    void listTasks();

    void completeTask(int id);

    void deleteTask(sqlite3* db, int taskID);

    std::unordered_map<int, Task> getTasks();
};



#endif //TASKMANAGER_H
