#include "command_stack.hpp"
#include <stdexcept>

CommandStack::CommandStack() {
    recent = nullptr;
}

CommandStack::~CommandStack() { // free up dynamically allocated memory
    while(!recent) {
        Node* old_recent = recent;
        recent = recent->next;
        delete old_recent;
    }
}

bool CommandStack::isEmpty() {
    return recent == nullptr;
}

void CommandStack::push(string current_command) {
    Node* new_recent = new Node;
    new_recent->data = current_command;
    new_recent->next = recent; // sets next to top
    recent = new_recent; // top reassigned
}

string CommandStack::pop() {
    if (isEmpty()) {
        return ""; // no history so return an empty string
    }
    Node* old_recent = recent;
    string res = recent->data;
    recent = recent->next;
    delete old_recent;
    return res;
}
