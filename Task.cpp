#include "Task.h"

Task::Task(std::string desc, std::string dl, int prio) 
    : description(desc), deadline(dl), priority(prio), completed(false) {}

std::string Task::getPriorityString() const {
    switch(priority) {
        case 1: return "High";
        case 2: return "Medium";
        case 3: return "Low";
        default: return "Unknown";
    }
}