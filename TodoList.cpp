#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

bool isValidDate(const string& date) {
    if(date.length() != 10) return false;
    if(date[2] != '-' || date[5] != '-') return false;

    // Check if all other characters are digits
    for(int i = 0; i < 10; i++) {
        if(i == 2 || i == 5) continue;
        if(!isdigit(date[i])) return false;
    }

    // Extract month, day, year
    int month = stoi(date.substr(0, 2));
    int day = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // Basic validation
    if(month < 1 || month > 12) return false;
    if(day < 1 || day > 31) return false;
    if(year < 1900 || year > 2100) return false;

    return true;
}

string getDateOneYearFromNow() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int year = 1900 + ltm->tm_year + 1; // Add 1 year

    stringstream ss;
    ss << setfill('0') << setw(2) << month << "-"
       << setfill('0') << setw(2) << day << "-"
       << year;

    return ss.str();
}

void TodoList::addTask() {
    string desc, deadline;
    int priority;

    cout << "\nEnter task description: ";
    getline(cin, desc);

    cout << "Enter deadline (MM-DD-YYYY): ";
    getline(cin, deadline);

    // Validate and set default if needed
    if(deadline.empty() || !isValidDate(deadline)) {
        deadline = getDateOneYearFromNow();
        cout << "Invalid date, default deadline given: 1 year.\n";
    }
    
    cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
    cin >> priority;
    
    if(priority < 1 || priority > 3) {
        cout << "Invalid priority. Setting to Medium.\n";
        priority = 2;
    }
    
    tasks.push_back(Task(desc, deadline, priority));
    cout << "\nTask added successfully!\n";
}

void TodoList::viewTasks() {
    if(tasks.empty()) {
        cout << "\nNo tasks in the list.\n";
        return;
    }
    
    cout << "\n" << string(100, '=') << "\n";
    cout << left << setw(5) << "No." 
         << setw(40) << "Description" 
         << setw(15) << "Deadline" 
         << setw(10) << "Priority"
         << setw(10) << "Status" << "\n";
    cout << string(100, '=') << "\n";
    
    for(size_t i = 0; i < tasks.size(); i++) {
        cout << left << setw(5) << i + 1
             << setw(40) << (tasks[i].getDescription().length() > 38 ? 
                             tasks[i].getDescription().substr(0, 35) + "..." : 
                             tasks[i].getDescription())
             << setw(15) << tasks[i].getDeadline()
             << setw(10) << tasks[i].getPriorityString()
             << setw(10) << (tasks[i].isCompleted() ? "Done" : "Pending") << "\n";
    }
    cout << string(100, '=') << "\n";
}

void TodoList::sortByPriority() {
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.getPriority() < b.getPriority();
    });
    cout << "\nTasks sorted by priority.\n";
}

void TodoList::sortByDeadline() {
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.getDeadline() < b.getDeadline();
    });
    cout << "\nTasks sorted by deadline.\n";
}

void TodoList::markComplete() {
    if(tasks.empty()) {
        cout << "\nNo tasks to mark as complete.\n";
        return;
    }
    
    viewTasks();
    int taskNum;
    cout << "\nEnter task number to mark as complete: ";
    cin >> taskNum;
    
    if(taskNum < 1 || taskNum > (int)tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    
    tasks[taskNum - 1].setCompleted(true);
    cout << "Task marked as complete!\n";
}

void TodoList::deleteTask() {
    if(tasks.empty()) {
        cout << "\nNo tasks to delete.\n";
        return;
    }
    
    viewTasks();
    int taskNum;
    cout << "\nEnter task number to delete: ";
    cin >> taskNum;
    
    if(taskNum < 1 || taskNum > (int)tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    
    tasks.erase(tasks.begin() + taskNum - 1);
    cout << "Task deleted successfully!\n";
}

void TodoList::saveTasks() {
    ofstream file(filename);
    if(!file) {
        cout << "\nError: Could not save tasks to file.\n";
        return;
    }
    
    for(const auto& task : tasks) {
        file << task.getDescription() << "|"
             << task.getDeadline() << "|"
             << task.getPriority() << "|"
             << task.isCompleted() << "\n";
    }
    
    file.close();
    cout << "\nTasks saved successfully!\n";
}

void TodoList::loadTasks() {
    ifstream file(filename);
    if(!file) {
        cout << "\nNo saved tasks found.\n";
        return;
    }
    
    tasks.clear();
    string line;
    int count = 0;
    
    while(getline(file, line)) {
        stringstream ss(line);
        string desc, deadline;
        int priority;
        bool completed;
        
        getline(ss, desc, '|');
        getline(ss, deadline, '|');
        ss >> priority;
        ss.ignore();
        ss >> completed;
        
        Task task(desc, deadline, priority);
        task.setCompleted(completed);
        tasks.push_back(task);
        count++;
    }
    
    file.close();
    cout << "\n" << count << " task(s) loaded successfully!\n";
}
