#include "../include/command.hpp"

// base class for commands
Command::Command(const vector<string>& new_tokens) {
    command_tokens = new_tokens;
    num_tokens = new_tokens.size();
    current_path = fs::current_path();
    current_path += "/"; // directory suffix
}

Command::~Command() {
    /* Clean up resources */
}
