//
// Created by Connor Bethel on 05/04/2025.
//

#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    int id{};
    std::string title;
    std::string description;
    bool completed{};

public:
    Task() = default;
    Task(int id, const std::string& title, const std::string& description, bool completed);

    void setID(int id);
    int getID() const;

    void setTitle(std::string title);
    std::string getTitle();

    void setDescription(std::string description);
    std::string getDescription();

    bool getCompleted() const;
    void setCompleted(bool completed);
};



#endif //TASK_H

