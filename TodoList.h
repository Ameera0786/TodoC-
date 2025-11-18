#ifndef TODOLIST_H
#define TODOLIST_H

#include "Task.h"
#include <vector>
#include <string>

class TodoList {
private:
    std::vector<Task> tasks;
    const std::string filename = "tasks.txt";
    
public:
    void addTask();
    void viewTasks();
    void sortByPriority();
    void sortByDeadline();
    void markComplete();
    void deleteTask();
    void saveTasks();
    void loadTasks();
    bool isEmpty() const { return tasks.empty(); }
};

#endif