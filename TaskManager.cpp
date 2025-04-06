//
// Created by Connor Bethel on 05/04/2025.
//

#include "TaskManager.h"

#include <iostream>

#include "Persistence.h"

void TaskManager::createTask(sqlite3* db) {
    std::string title;
    std::string description;

    std::cout << "Title: ";
    std::cin >> title;
    std::cout << "Description: ";
    std::cin >> description;

    Task newTask(0, title, description, false);
    Persistence::insertTask(db, newTask, *this);
}

void TaskManager::addTask(Task& task) {
    tasks.emplace(task.getID(), task);
    std::cout << "Task " << task.getTitle() << " created and added successfully.\n" << std::endl;
}

void TaskManager::listTasks() {
    for (auto& [id, task] : tasks) {
        std::cout << "[ID]          - " << id << std::endl;
        std::cout << "[Title]       - " << task.getTitle() << std::endl;
        std::cout << "[Description] - " << task.getDescription() << std::endl;
        std::cout << "[Status]      - " << (task.getCompleted() ? "Completed.\n" : "Un-completed.\n") << std::endl;
    }
}

void TaskManager::completeTask(const int id) {
    for (auto& [taskID, task] : tasks) {
        if (taskID == id) {
            task.setCompleted(true);
            std::cout << "Task " << task.getTitle() << " marked as complete.\n" << std::endl;
            return;
        }
    }
    std::cerr << "Task ID: " << id << " not found" << std::endl;
}

void TaskManager::deleteTask(sqlite3 *db, const int taskID) {
    if (tasks.contains(taskID)) {
        tasks.erase(taskID);
        Persistence::deleteTask(db, taskID);
        std::cout << "Task with ID " << taskID << " has been removed.\n" << std::endl;
    } else {
        std::cout << "Task with ID " << taskID << " not found.\n" << std::endl;
    }
}

std::unordered_map<int, Task> TaskManager::getTasks() {
    return tasks;
}





