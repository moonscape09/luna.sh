#include <iostream>
#include "command.hpp"

Command::Command(vector<string> new_tokens) {
    command_tokens = new_tokens;
}

Command::~Command() {
    /* Clean up resources */
}

/**
 * @brief  Echoes out user input
 *
 * This function prints out the user input after the "echo" command.
 *
 */
void EchoCommand::echo_fn() {
    for (size_t i = 1; i < command_tokens.size(); i ++) {
        cout << command_tokens[i] << " ";
    }
    cout << "\n";
}
