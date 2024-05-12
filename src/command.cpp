#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "command.hpp"
namespace fs = filesystem;

Command::Command(vector<string> new_tokens) {
    command_tokens = new_tokens;
    num_tokens = new_tokens.size();
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
    if (num_tokens > 1) {
        for (size_t i = 1; i < num_tokens; i ++) {
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
    if (num_tokens > 1) {
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
   if (num_tokens == 1 || command_tokens[1] == "~") {
        fs::path p = fs::current_path();
        fs::current_path(getenv("HOME"));
        return;
   // case 2: too many arguments passed in
   } else if (num_tokens > 2) {
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
    if (num_tokens == 1) {
        cout << "mkdir: Please provide a directory name." << "\n";
        return;
    }
    for (size_t i = 1; i < num_tokens; i ++) {
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

    if (num_tokens == 1) {
        cout << command_tokens[0] << ": Please specify a " << item_type << "\n";
        return;
    }
    for (size_t i = 1; i < num_tokens; i ++) {

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


/**
 * @brief helper function to list all contents
 *
 * This is a helper to ls_fn() for actually listing all the contents of a current directory
 * and formats that output to display relative path.
 *
 * @param curr_path: a string that represents the absolute path of the current or specified directory
 *
 * @return a string that lists relative paths to the items living in the directory arg
 */

string ls_fn_helper(string curr_path) {
    string list_of_items = "";
    for (fs::directory_entry dir : fs::directory_iterator(curr_path)) {
        string item = dir.path();
        list_of_items = list_of_items + item.substr(item.find_last_of("/") + 1) + "    ";
    }
    return list_of_items;
}

/**
 * @brief List contents of current directory.
 *
 * This function handles user inputs for `ls` command
 * and lists files and directories in current directory user is in.
 * Also handles filename/dirname input after "ls" and formats the output accordingly.
 *
 */
void LsCommand::ls_fn() {

    string directories_string = "";
    string files_string = "";

    // handle case for when user specifies files or directories
    if (num_tokens > 1) {

        for (size_t i = 1; i < num_tokens; i++) {

            // get path of current iterable item
            fs::path item_to_list = fs::current_path().append(command_tokens[i]);

            // check if path to item exists
            if (!fs::exists(item_to_list)) {
                cout << "ls: No such file or directory: " << command_tokens[i] << "\n";
                continue;
            }

            if (!fs::is_directory(item_to_list)) { // if current iterable item is a file then add to files string
                files_string = files_string + command_tokens[i] + "    ";
            } else { // if current iterable item is a directory then add relative path to directory string
                directories_string = directories_string + command_tokens[i] + "/: \n" + ls_fn_helper(item_to_list)
                    + (num_tokens > 2 ? "\n\n" : "\n"); // case "ls dir1" only needs one newline
            }
        }

        // print files first
        cout << files_string << (files_string != "" ? "\n" : ""); // case: "ls file1 file2" output should be terminated by newline
        cout << (files_string != "" && directories_string != "" ? "\n" : ""); // case: "ls file1 file2 dir1" output should have newline between dir and files

        // lists of multiple directories' contents are seperated by two newlines so remove the second newline after the last directory's contents
        if (num_tokens > 2) {
            directories_string.pop_back();
        }

        // then print directories
        cout << directories_string;

        return;
    }

    // if input is just `ls` then call helper to simply list all the contents of current directory
    //TODO EMPTY `ls`;
    cout << ls_fn_helper(fs::current_path()) << "\n";
}


/**
 * @brief Move/rename contents.
 *
 * This function handles user input for the `mv` command. It supports renaming files, or moving
 * contents to other directories.
 *
 */

void MvCommand::mv_fn() {

    // user has to specify a source and a target
    if (num_tokens <= 2) {
        cout << "mv: " << "Please provide a source and target!" << "\n";
        return;
    }

    string target = command_tokens[num_tokens - 1];
    fs::path path_to_target = fs::current_path() / target;

    fs::path path_to_source = fs::current_path();

    if (fs::is_directory(path_to_target)) {
        //iterate over all the sources and move them to target destination
        for (size_t i = 1; i < num_tokens - 1; i++) {
            fs::path source = path_to_source / command_tokens[i];

            // if current iterable source doesn't exist, move on to next item
            if (!fs::exists(source)) {
                cout << "mv: No such file or directory: " << command_tokens[i] << "\n";
                continue;
            }
            fs::rename(source, path_to_target / command_tokens[i]);
        }
        return;
    }

    // when three or more files/dirs are given, the target should be perceived as a directory
    if (num_tokens > 3) {
        cout << "mv: " << target << " is not a directory" << "\n";
        return;
    }

    // if source doesn't exist
    if (!fs::exists(path_to_source / command_tokens[1])) {
        cout << "mv: No such file or directory: " + command_tokens[1] << "\n";
        return;
    }

    // edge case: when user attempts to move directory to a file
    if (fs::is_directory(path_to_source / command_tokens[1]) && fs::is_regular_file(path_to_target)) {
        cout << "mv: " << "cannot rename a directory to name of an existing file: " << target << "\n";
        return;
    }

    fs::rename(path_to_source / command_tokens[1], path_to_target);
}
