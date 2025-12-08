#include "Task.h"

// Constructor - initializes task with desc, deadline, priority
Task::Task(const std::string& desc, const std::string& dl, int prio, bool done)
    : description(desc), deadline(dl), priority(prio), completed(done) {}

// Getters
const std::string& Task::getDescription() const { return description; }
const std::string& Task::getDeadline() const { return deadline; }
int Task::getPriority() const { return priority; }
bool Task::isCompleted() const { return completed; }

// Setters
void Task::setDescription(const std::string& desc) { description = desc; }
void Task::setDeadline(const std::string& dl) { deadline = dl; }
void Task::setPriority(int prio) { priority = prio; }
void Task::setCompleted(bool done) { completed = done; }

// Returns readable label
std::string Task::getPriorityLabel() const {
    switch(priority) {
        case 1: return "High";
        case 2: return "Medium";
        case 3: return "Low";
        default: return "Unknown";
    }
}
