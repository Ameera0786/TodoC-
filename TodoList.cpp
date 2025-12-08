#include "TodoList.h"
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>

// Validates date
bool TodoList::isValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }

    int year  = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day   = std::stoi(date.substr(8, 2));

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

// Default date
std::string TodoList::getDateOneYearFromNow() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    int year  = 1900 + ltm->tm_year + 1; // add 1 year
    int month = 1 + ltm->tm_mon;
    int day   = ltm->tm_mday;

    std::stringstream ss;
    ss << year << "-"
       << std::setfill('0') << std::setw(2) << month << "-"
       << std::setfill('0') << std::setw(2) << day;

    return ss.str();
}

// Adds task to list
void TodoList::add(const Task& task) {
    tasks.push_back(task);
}

// Removes from list
void TodoList::remove(int index) {
    tasks.erase(tasks.begin() + index);
}

// Marks complete
void TodoList::markComplete(int index) {
    tasks[index].setCompleted(true);
}

// Gets all tasks
const std::vector<Task>& TodoList::getTasks() const {
    return tasks;
}

// Sets tasks to new tasks
void TodoList::setTasks(const std::vector<Task>& newTasks) {
    tasks = newTasks;
}

// Sorts by priority
void TodoList::sortByPriority() {
    std::sort(tasks.begin(), tasks.end(),
              [](const Task& a, const Task& b){
                  return a.getPriority() < b.getPriority();
              });
}

// Sorts by deadline
void TodoList::sortByDeadline() {
    std::sort(tasks.begin(), tasks.end(),
              [](const Task& a, const Task& b){
                  return a.getDeadline() < b.getDeadline();
              });
}
