#include "command.hpp"
class CommandList {
    struct CommandNode {
        Command command;
        CommandNode* next;
    };
public:
    CommandList();
    ~CommandList();
    CommandNode* head;
    void insert_command(const Command& command_to_insert);
}
