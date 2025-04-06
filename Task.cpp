//
// Created by Connor Bethel on 05/04/2025.
//

#include "Task.h"

#include <utility>

Task::Task(const int id, const std::string& title, const std::string& description, const bool completed) {
    this->id = id;
    this->title = title;
    this->description = description;
    this->completed = completed;
}

int Task::getID() const {
    return this->id;
}
void Task::setID(const int id) {
    this->id = id;
}

std::string Task::getTitle() {
    return this->title;
}
void Task::setTitle(std::string title) {
    this->title = std::move(title);
}


std::string Task::getDescription() {
    return this->description;
}
void Task::setDescription(std::string description) {
    this->description = std::move(description);
}

bool Task::getCompleted() const {
    return this->completed;
}
void Task::setCompleted(const bool completed) {
    this->completed = completed;
}





