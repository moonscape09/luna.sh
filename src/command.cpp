#include "../include/command.hpp"

// base class for commands
Command::Command(const vector<string>& new_tokens) {
    command_tokens = new_tokens;
    num_tokens = new_tokens.size();
    current_path = fs::current_path();
    current_path += "/"; // directory suffix
}

/**
 * @brief helper function to disable all options
 *
 * This function is called in the option handling process
 * whenever any option has been explicitly mentioned in user
 * input. This disables any options that are part of the
 * default behaviour of the command (when options are not
 * defined in input).
 *
 */
void Command::disable_all_options() {
    for (auto& option : command_options) {
        option.second = false; // disable all options to false
    }
}

/**
 * @brief helper function to enable filtered options
 *
 * This function is called in the option handling process
 * to enable the inputted options by setting them to true in the
 * command_options map. This will lay out the behaviour of the
 * command based on the options selected. If there is an illegal
 * option found, a flag for invalid option is set to true and
 * then the function terminates. This flag, when true, will prevent
 * the main command functionality (i.e wc_fn()) to execute.
 *
 * @param curr_path: a string that represents a token defined as an option
 *
 */
void Command::set_command_options(const string& options_token) {
    for (char option : options_token) {
        if (option == '-') continue; //skip the option indicator

        if (command_options.find(option) != command_options.end()) command_options[option] = true;
        else {
            result += command_tokens[0] + ": illegal option: " + option + "\n";
            invalid_option_found = true;
            return;
        }
    }
}

/**
 * @brief function used for handling options
 *
 * This function handles input involving any options (prefixed
 * by '-'). It calls the helper functions above to address
 * various cases that can come with user input options.
 *
 */
void Command::options_handler() {
    // search for options (which are prefixed by '-')
    for (string token : command_tokens) {
        if (token[0] != '-') continue;

        if (disable_all_options_if_explicit_found == true) {
            disable_all_options();
            disable_all_options_if_explicit_found = false;
        }

        set_command_options(token);
    }
}

Command::~Command() {
    /* Clean up resources */
}
