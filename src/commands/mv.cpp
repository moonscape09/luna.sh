#include "../../include/command.hpp"
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
        result = "mv: Please provide a source and target!\n";
        return;
    }

    string target = command_tokens[num_tokens - 1];
    fs::path path_to_target = current_path + target;

    fs::path path_to_source = current_path;

    if (fs::is_directory(path_to_target)) {
        //iterate over all the sources and move them to target destination
        for (size_t i = 1; i < num_tokens - 1; i++) {
            fs::path source = path_to_source / command_tokens[i];

            // if current iterable source doesn't exist, move on to next item
            if (!fs::exists(source)) {
                result = result + "mv: No such file or directory: " + command_tokens[i] + "\n";
                continue;
            }
            fs::rename(source, path_to_target / command_tokens[i]);
        }
        return;
    }

    // when three or more files/dirs are given, the target should be perceived as a directory
    if (num_tokens > 3) {
        result = "mv: " + target + " is not a directory\n";
        return;
    }

    // if source doesn't exist
    if (!fs::exists(path_to_source / command_tokens[1])) {
        result = "mv: No such file or directory " + command_tokens[1] + "\n";
        return;
    }

    // edge case: when user attempts to move directory to a file
    if (fs::is_directory(path_to_source / command_tokens[1]) && fs::is_regular_file(path_to_target)) {
        result = "mv: cannot rename a directory to name of an existing file: " + target + "\n";
        return;
    }

    fs::rename(path_to_source / command_tokens[1], path_to_target);
}
