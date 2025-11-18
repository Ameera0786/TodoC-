#include "TodoList.h"
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>

bool isValidDate(const std::string& date) {
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


std::string getDateOneYearFromNow() {
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


void TodoList::add(const Task& task) {
    tasks.push_back(task);
}

void TodoList::remove(int index) {
    tasks.erase(tasks.begin() + index);
}

void TodoList::markComplete(int index) {
    tasks[index].setCompleted(true);
}

const std::vector<Task>& TodoList::getTasks() const {
    return tasks;
}

void TodoList::setTasks(const std::vector<Task>& newTasks) {
    tasks = newTasks;
}

void TodoList::sortByPriority() {
    std::sort(tasks.begin(), tasks.end(),
              [](const Task& a, const Task& b){
                  return a.getPriority() < b.getPriority();
              });
}

void TodoList::sortByDeadline() {
    std::sort(tasks.begin(), tasks.end(),
              [](const Task& a, const Task& b){
                  return a.getDeadline() < b.getDeadline();
              });
}

bool TodoList::isValidDate(const std::string& date) const {
    return ::isValidDate(date); // use your existing function
}

std::string TodoList::getDefaultDeadline() const {
    return getDateOneYearFromNow(); // your existing helper
}
