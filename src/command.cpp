#include <iostream>
#include <filesystem>
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
    size_t input_size = command_tokens.size();
    if (input_size > 1) {
        for (size_t i = 1; i < input_size; i ++) {
            cout << command_tokens[i] << " ";
        }
    }
}


/**
 * @brief  Prints current directory user is in
 *
 * This function prints out the full path leading up to the directory the user is currently in.
 *
 */
void PwdCommand::pwd_fn() {
    if (command_tokens.size() > 1) {
        cout << "pwd: Only write pwd!";
    } else {
        string fullpath = filesystem::current_path();
        size_t first_quotation = fullpath.find("\"");
        cout << fullpath.substr(first_quotation + 1, fullpath.size() - first_quotation - 1);
    }
}
