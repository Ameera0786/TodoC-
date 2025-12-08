#include "TaskRepository.h"
#include <fstream>
#include <sstream>

// Constructor - stores filename where tasks are saved
TaskRepository::TaskRepository(const std::string& file)
    : filename(file) {}

// Loads them from file and returns as vector
std::vector<Task> TaskRepository::load() const {
    std::vector<Task> tasks;
    std::ifstream file(filename);

    if(!file) return tasks;

    std::string line;
    // Each line is a single task
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

// Saves tasks into file
void TaskRepository::save(const std::vector<Task>& tasks) const {
    std::ofstream file(filename);
    for(const Task& t : tasks) {
        file << t.getDescription() << "|"
             << t.getDeadline() << "|"
             << t.getPriority() << " "
             << t.isCompleted() << "\n";
    }
}
