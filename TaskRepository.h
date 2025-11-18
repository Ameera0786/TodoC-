#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H

#include <vector>
#include <string>
#include "Task.h"

class TaskRepository {
private:
    std::string filename;

public:
    TaskRepository(const std::string& file = "tasks.txt");

    std::vector<Task> load() const;
    void save(const std::vector<Task>& tasks) const;
};

#endif
