#ifndef TODOUI_H
#define TODOUI_H

#include "TodoList.h"
#include "TaskRepository.h"

class TodoUI {
private:
    TodoList& todo;
    TaskRepository& repo;

public:
    TodoUI(TodoList& list, TaskRepository& r);

    void run();     // main loop
    void displayMenu() const;

private:
    void uiAddTask();
    void uiViewTasks() const;
    void uiSortByPriority();
    void uiSortByDeadline();
    void uiMarkComplete();
    void uiDeleteTask();
};

#endif
