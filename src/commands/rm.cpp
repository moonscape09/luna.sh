#include "../../include/command.hpp"
/**
 * @brief Remove a specified file/directory
 *
 * This function removes a specified file/directory and throws an appropriate error message if the directory does not exist.
 *
 */
void RmCommand::rm_fn() {
    string item_type = is_rmdir ? "directory" : "file";

    if (num_tokens == 1) {
        result = command_tokens[0] + ": Please specify a " + item_type + "\n";
        return;
    }
    for (size_t i = 1; i < num_tokens; i ++) {

        fs::path item_to_remove = current_path + command_tokens[i];

        if (!fs::exists(item_to_remove)) {
            result = command_tokens[0] + ": " + item_type + " doesn't exist!" + "\n";
            return;
        } else if (command_tokens[i] == ".") {
            result = command_tokens[0] + ": " + "Invalid argument" + "\n";
            return;
        }

        try {

            if (!is_rmdir && fs::is_directory(item_to_remove)) {
                result = command_tokens[0] + ": " + command_tokens[i] + " is a directory" + "\n";
                return;
            } else if (is_rmdir && !fs::is_directory(item_to_remove)) {
                result = command_tokens[0] + ": " + command_tokens[i] + " is not a directory" + "\n";
                return;
            }

            fs::remove(item_to_remove);
        } catch(exception& e) {

            string errormsg = e.what();

            if (errormsg.find("Directory not empty") != string::npos) {
                result = "rmdir: Directory not empty: " + command_tokens[1] + "\n";
            }
        }
    }
}
