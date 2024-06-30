#include <fstream>
#include "../../include/command.hpp"
/**
 * @brief Display contents of a file.
 *
 * This function handles user input for the `cat` command. It is used
 * to list contents of the file arguments.
 *
 */

void CatCommand::cat_fn() {
    if (num_tokens <= 1) {
        result = "cat: Not supported yet.\n";
        return;
    }
    for (size_t i = 1; i < num_tokens; i++) {
        fs::path item_to_cat = current_path + command_tokens[i];
        if (!fs::exists(item_to_cat)) {
            result = result + "cat: No such file: " + command_tokens[i] + "\n";
            continue;
        }

        if (fs::is_directory(item_to_cat)) {
            result = result + "cat: " + command_tokens[i] + " is a directory\n";
            continue;
        }

        result = result + command_tokens[i] + ": \n\n";
        string file_contents;
        ifstream curr_file(command_tokens[i]);
        while (getline(curr_file, file_contents)) {
            result = result + file_contents + "\n";
        }
        result = result + "\n";
    }
}
