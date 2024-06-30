#include <cstdlib>
#include "../../include/command.hpp"
/**
 * @brief Navigate to directory user inputs
 *
 * This function goes to the directory path that the user specifies.
 *
 */
void CdCommand::cd_fn() {

   // case 1: home directory
   if (num_tokens == 1 || command_tokens[1] == "~") {
        fs::current_path(getenv("HOME"));
        return;
   // case 2: too many arguments passed in
   } else if (num_tokens > 2) {
        result = "cd: Too many arguments, only write one directory!\n";
        return;
   // case 3: absolute and relative paths
    }
    try {
        fs::current_path(command_tokens[1]);
    } catch (exception& e) {
        string error = e.what();
        if (error.find("Not a directory") != string::npos) {
            result = "cd: Not a directory: " + command_tokens[1] + "\n";
        } else if (error.find("No such file or directory") != string::npos) {
            result = "cd: No such file or directory: " + command_tokens[1] + "\n";
        }
    }
}
