#ifndef TODOLIST_H
#define TODOLIST_H

#include <vector>
#include "Task.h"

class TodoList {
private:
    std::vector<Task> tasks;

public:
    void add(const Task& task);
    void remove(int index);
    void markComplete(int index);

    const std::vector<Task>& getTasks() const;

    void sortByPriority();
    void sortByDeadline();

    void setTasks(const std::vector<Task>& newTasks);
    bool isValidDate(const std::string& date) const;
    std::string getDefaultDeadline() const;

};

#endif
