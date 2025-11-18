#include "TodoUI.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

TodoUI::TodoUI(TodoList& list, TaskRepository& r)
    : todo(list), repo(r) {}

void TodoUI::displayMenu() const {
    cout << "\n--- TODO LIST MANAGER ---\n";
    cout << "1. Add task\n";
    cout << "2. View tasks\n";
    cout << "3. Sort by priority\n";
    cout << "4. Sort by deadline\n";
    cout << "5. Mark complete\n";
    cout << "6. Delete task\n";
    cout << "0. Save & Exit\n";
}

void TodoUI::run() {
    todo.setTasks(repo.load());
    std::string input;
    int choice;

    do {
        displayMenu();
        cout << "Enter choice: ";
        getline(cin, input);  // read whole line

        try {
            choice = std::stoi(input); // convert string to int
        } catch(...) {
            cout << "Invalid input! Please enter a number 0-6.\n";
            continue;
        }

        switch(choice) {
            case 1: uiAddTask(); break;
            case 2: uiViewTasks(); break;
            case 3: uiSortByPriority(); break;
            case 4: uiSortByDeadline(); break;
            case 5: uiMarkComplete(); break;
            case 6: uiDeleteTask(); break;
            case 0: repo.save(todo.getTasks()); break;
            default:
                cout << "Invalid choice! Please enter 0-6.\n";
        }

    } while(choice != 0);
}


void TodoUI::uiAddTask() {
    string desc, dl, prInput;
    int pr;

    cout << "Description (leave empty for default): ";
    getline(cin, desc);
    if (desc.empty()) {
        desc = "Untitled Task";
        cout << "Default description applied.\n";
    }
    cout << "Deadline (YYYY-MM-DD, leave empty for default): ";
    getline(cin, dl);
    if (dl.empty() || !todo.isValidDate(dl)) {
        dl = todo.getDefaultDeadline();   // helper inside TodoList
        cout << "Default deadline set (1 year from today).\n";
    }
    cout << "Priority (1-3, default = Medium): ";
    getline(cin, prInput);
    try {
        pr = std::stoi(prInput);
    } catch(...) {
        pr = 2;  // default Medium
        cout << "Default priority set (Priority set to Medium).\n";
    }
    if (pr < 1 || pr > 3) {
        pr = 2;  // default Medium
        cout << "Default priority set (Priority set to Medium).\n";
    }
    cout << "Task added!\n";
    todo.add(Task(desc, dl, pr, false));
}

void TodoUI::uiViewTasks() const {
    const auto& list = todo.getTasks();
    if(list.empty()) {
        cout << "No tasks.\n";
        return;
    }

    cout << "-------------------------------------------------------------------------------\n";
    cout << left
         << setw(5)  << "No."
         << setw(25) << "Description"
         << setw(15) << "Deadline"
         << setw(10) << "Priority"
         << setw(10) << "Status"
         << "\n";
    cout << "-------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < list.size(); i++) {
        cout << left
             << setw(5)  << to_string(i+1) + "."
             << setw(25) << list[i].getDescription()
             << setw(15) << list[i].getDeadline()
             << setw(10) << list[i].getPriorityLabel()
             << setw(10) << (list[i].isCompleted() ? "DONE" : "PENDING")
             << "\n";
    }
}


void TodoUI::uiSortByPriority() {
    todo.sortByPriority();
}

void TodoUI::uiSortByDeadline() {
    todo.sortByDeadline();
}

void TodoUI::uiMarkComplete() {
    int n;
    cout << "Task number: ";
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // <-- clear leftover newline

    // Validate number
    if (!cin || n < 1 || n > (int)todo.getTasks().size()) {
        cout << "Invalid task number.\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    todo.markComplete(n - 1);
    cout << "Task marked complete!\n";
}

void TodoUI::uiDeleteTask() {
    int n;
    cout << "Task number: ";
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // <-- clear leftover newline

    if (!cin || n < 1 || n > (int)todo.getTasks().size()) {
        cout << "Invalid task number.\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    todo.remove(n - 1);
    cout << "Task deleted!\n";
}
