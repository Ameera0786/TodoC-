#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    std::string description;
    std::string deadline;
    int priority;
    bool completed;

public:
    Task(const std::string& desc = "",
         const std::string& dl = "",
         int prio = 2,
         bool done = false);

    // Getters
    const std::string& getDescription() const;
    const std::string& getDeadline() const;
    int getPriority() const;
    bool isCompleted() const;

    // Setters
    void setDescription(const std::string& desc);
    void setDeadline(const std::string& dl);
    void setPriority(int prio);
    void setCompleted(bool done);

    std::string getPriorityLabel() const;
};

#endif
