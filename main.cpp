#include "TodoList.h"
#include <iostream>

using namespace std;

void displayMenu() {
    cout << "\n----------------------------------\n";
    cout << "|       TODO LIST MANAGER          |\n";
    cout << "----------------------------------\n";
    cout << "1. Add new task\n";
    cout << "2. View all tasks\n";
    cout << "3. Sort by priority\n";
    cout << "4. Sort by deadline\n";
    cout << "5. Mark task as complete\n";
    cout << "6. Delete task\n";
    cout << "7. Save tasks\n";
    cout << "8. Load tasks\n";
    cout << "0. Exit\n";
    cout << "\nEnter your choice: ";
}

int main() {
    TodoList todoList;
    int choice;
    
    cout << "Welcome to Todo List Manager!\n";
    todoList.loadTasks(); // Auto-load tasks on startup
    
    do {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number (0-8). \n";
            continue;
        }

        cin.ignore(10000, '\n');

        switch(choice) {
            case 1:
                todoList.addTask();
                break;
            case 2:
                todoList.viewTasks();
                break;
            case 3:
                todoList.sortByPriority();
                todoList.viewTasks();
                break;
            case 4:
                todoList.sortByDeadline();
                todoList.viewTasks();
                break;
            case 5:
                todoList.markComplete();
                break;
            case 6:
                todoList.deleteTask();
                break;
            case 7:
                todoList.saveTasks();
                break;
            case 8:
                todoList.loadTasks();
                break;
            case 0:
                cout << "\nSaving tasks before exit...\n";
                todoList.saveTasks();
                cout << "Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while(choice != 0);
    
    return 0;
}