#include "command.hpp"
#include <iostream>
#include <readline/readline.h>
#include <cstring>

// doubly linked list implementation
struct CommandNode {
    Command command;
    CommandNode* next;
    CommandNode* prev;
    CommandNode(const Command& new_command) : command(new_command), next(nullptr), prev(nullptr) {};
};

class CommandHistory {
private:
    bool initialHistoryTraversal; // flag used for one-off case when most recent command doesn't show when new command history traversal begins
    CommandNode* head;
    CommandNode* iterator;
public:
    void go_down_history();
    void go_up_history();
    CommandHistory() {}; // default constructor used for initialization
    ~CommandHistory();
    void insert_command(const Command& command_to_insert);
};
