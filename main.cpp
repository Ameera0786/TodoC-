#include "TodoList.h"
#include "TaskRepository.h"
#include "TodoUI.h"

int main() {
    TodoList list;
    TaskRepository repo("tasks.txt");
    TodoUI ui(list, repo);

    ui.run();
    return 0;
}
