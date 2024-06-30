#include "../../include/command.hpp"
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

string ls_fn_helper(const string& curr_path) {
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
            fs::path item_to_list = current_path + command_tokens[i];

            // check if path to item exists
            if (!fs::exists(item_to_list)) {
                result = result + "ls: No such file or directory: " + command_tokens[i] + "\n";
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
        result = result + files_string + (files_string != "" ? "\n" : ""); // case: "ls file1 file2" output should be terminated by newline
        result = result + (files_string != "" && directories_string != "" ? "\n" : ""); // case: "ls file1 file2 dir1" output should have newline between dir and files

        // lists of multiple directories' contents are seperated by two newlines so remove the second newline after the last directory's contents
        if (num_tokens > 2) {
            directories_string.pop_back();
        }

        // then print directories
        result = result + directories_string;

        return;
    }

    string list_of_items = ls_fn_helper(current_path);

    // if input is just `ls` then call helper to simply list all the contents of current directory
    result = result + list_of_items + (list_of_items == "" ? "" : "\n");
}
