#include <iostream>
#include <sstream>
#include "command.hpp"

Command::Command(string new_command) {
    command_tokens = tokenize(new_command);
}

Command::~Command() {
    /* Clean up resources */
}

/**
 * @brief  Tokenizes user input string
 * 
 * This function takes in the user input string and tokenizes by white space.
 * 
 * @param user_input:  string from the standard input stream to tokenize
 * 
 * @return vector of tokens for command parsing
 */
vector<string> Command::tokenize(string user_input) {
    istringstream iss(user_input);
    vector<string> tokens;
    string token;

    // extraction operator default delimeter is whitespace
    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}