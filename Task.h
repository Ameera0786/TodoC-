#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    std::string description;
    std::string deadline;
    int priority; // 1 = High, 2 = Medium, 3 = Low
    bool completed;
    
public:
    Task(std::string desc, std::string dl, int prio);
    
    // Getters
    std::string getDescription() const { return description; }
    std::string getDeadline() const { return deadline; }
    int getPriority() const { return priority; }
    bool isCompleted() const { return completed; }
    std::string getPriorityString() const;
    
    // Setters
    void setCompleted(bool status) { completed = status; }
};

#endif
