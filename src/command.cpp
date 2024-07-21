#include "../include/command.hpp"

// base class for commands
Command::Command(const vector<string>& new_tokens) {
    command_tokens = new_tokens;
    num_tokens = new_tokens.size();
    current_path = fs::current_path();
    current_path += "/"; // directory suffix
}

void Command::disable_all_options() {
    for (auto& option : command_options) {
        option.second = false; // disable all options to false
    }
}

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
