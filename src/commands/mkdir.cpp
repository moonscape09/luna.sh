#include "../../include/command.hpp"
/**
 * @brief Create a directory with name argument
 *
 * This function creates a directory named as user input after command.
 *
 */
void MkDirCommand::mkdir_fn() {
    if (num_tokens == 1) {
        result = "mkdir: Please provide a directory name.\n";
        return;
    }
    for (size_t i = 1; i < num_tokens; i ++) {
        fs::path path_to_new_dir = current_path + command_tokens[i];
        if (fs::exists(path_to_new_dir)) {
            result = "mkdir: " + command_tokens[i] + " already exists!" + "\n";
            return;
        }
        fs::create_directory(path_to_new_dir);
    }
}
