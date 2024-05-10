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
        return;
    }
    string fullpath = fs::current_path();
    size_t first_quotation = fullpath.find("\"");
    cout << fullpath.substr(first_quotation + 1, fullpath.size() - first_quotation - 1) << "\n";
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
        return;
   // case 2: too many arguments passed in
   } else if (command_tokens.size() > 2) {
        cout << "cd: Too many arguments, only write one directory!" << "\n";
        return;
   // case 3: absolute and relative paths
    }
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



/**
 * @brief Create a directory with name argument
 *
 * This function creates a directory named as user input after command.
 *
 */
void MkDirCommand::mkdir_fn() {
    if (command_tokens.size() == 1) {
        cout << "mkdir: Please provide a directory name." << "\n";
        return;
    }
    for (size_t i = 1; i < command_tokens.size(); i ++) {
        fs::path path_to_new_dir = fs::current_path().append(command_tokens[i]);
        if (fs::exists(path_to_new_dir)) {
            cout << "mkdir: " << command_tokens[i] << " already exists!" << "\n";
            return;
        }
        fs::create_directory(path_to_new_dir);
    }
}


/**
 * @brief Remove a specified file/directory
 *
 * This function removes a specified file/directory and throws an appropriate error message if the directory does not exist.
 *
 */
void RmCommand::rm_fn() {
    string item_type = is_rmdir ? "directory" : "file";

    if (command_tokens.size() == 1) {
        cout << command_tokens[0] << ": Please specify a " << item_type << "\n";
        return;
    }
    for (size_t i = 1; i < command_tokens.size(); i ++) {

        fs::path item_to_remove = fs::current_path().append(command_tokens[i]);

        if (!fs::exists(item_to_remove)) {
            cout << command_tokens[0] << ": " << item_type << " doesn't exist!" << "\n";
            return;
        } else if (command_tokens[i] == ".") {
            cout << command_tokens[0] << ": " << "Invalid argument" << "\n";
            return;
        }

        try {

            if (!is_rmdir && fs::is_directory(item_to_remove)) {
                cout << command_tokens[0] << ": " << command_tokens[i] << " is a directory" << "\n";
                return;
            } else if (is_rmdir && !fs::is_directory(item_to_remove)) {
                cout << command_tokens[0]  << ": " << command_tokens[i] << " is not a directory" << "\n";
                return;
            }

            fs::remove(item_to_remove);
        } catch(exception& e) {

            string errormsg = e.what();

            if (errormsg.find("Directory not empty") != string::npos) {
                cout << "rmdir: Directory not empty: " << command_tokens[1] << "\n";
            }
        }
    }
}
