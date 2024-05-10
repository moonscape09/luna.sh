#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "command.hpp"
namespace fs = filesystem;

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
        cout << "pwd: Only write pwd!" << "\n";
    } else {
        string fullpath = fs::current_path();
        size_t first_quotation = fullpath.find("\"");
        cout << fullpath.substr(first_quotation + 1, fullpath.size() - first_quotation - 1) << "\n";
    }
}

/**
 * @brief Navigate to directory user inputs
 *
 * This function goes to the directory path that the user specifies.
 *
 */
void CdCommand::cd_fn() {

   // case 1: home directory
   if (command_tokens.size() == 1 || command_tokens[1] == "~") {
        fs::path p = fs::current_path();
        fs::current_path(getenv("HOME"));

   // case 2: too many arguments passed in
   } else if (command_tokens.size() > 2) {
        cout << "cd: Too many arguments, only write one directory!" << "\n";

   // case 3: absolute and relative paths
   } else {
        try {
            fs::current_path(command_tokens[1]);
        } catch (exception& e) {
            string error = e.what();
            if (error.find("Not a directory") != string::npos) {
                cout << "cd: Not a directory: " << command_tokens[1] << "\n";
            } else if (error.find("No such file or directory") != string::npos) {
                cout << "cd: No such file or directory: " << command_tokens[1] << "\n";
            }
        }
   }

}
