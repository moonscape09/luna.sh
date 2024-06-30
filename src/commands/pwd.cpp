#include "../../include/command.hpp"
/**
 * @brief  Prints current directory user is in
 *
 * This function prints out the full path leading up to the directory the user is currently in.
 *
 */
void PwdCommand::pwd_fn() {
    if (num_tokens > 1) {
        result = "pwd: Only write pwd!\n";
        return;
    }
    size_t first_quotation = current_path.find("\"");
    result = current_path.substr(first_quotation + 1, current_path.size() - first_quotation - 1) + "\n";
}
