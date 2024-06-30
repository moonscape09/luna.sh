#include "../../include/command.hpp"
/**
 * @brief  Echoes out user input
 *
 * This function prints out the user input after the "echo" command.
 *
 */
void EchoCommand::echo_fn() {
    if (num_tokens > 1) {
        for (size_t i = 1; i < num_tokens; i ++) {
            result = result + command_tokens[i] + " ";
        }
    }
}
