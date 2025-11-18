#include "TaskRepository.h"
#include <fstream>
#include <sstream>

TaskRepository::TaskRepository(const std::string& file)
    : filename(file) {}

std::vector<Task> TaskRepository::load() const {
    std::vector<Task> tasks;
    std::ifstream file(filename);

    if(!file) return tasks;

    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string desc, deadline;
        int prio;
        bool done;

        getline(ss, desc, '|');
        getline(ss, deadline, '|');
        ss >> prio >> done;

        tasks.emplace_back(desc, deadline, prio, done);
    }
    return tasks;
}

void TaskRepository::save(const std::vector<Task>& tasks) const {
    std::ofstream file(filename);
    for(const Task& t : tasks) {
        file << t.getDescription() << "|"
             << t.getDeadline() << "|"
             << t.getPriority() << " "
             << t.isCompleted() << "\n";
    }
}
