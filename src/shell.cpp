#include <cstddef>
#include <cstring>
#include <iostream>
#include <sstream>
#include "../include/shell.hpp"
#include <stdlib.h>
#include <stdio.h>

CommandHistory Shell::command_history;

// callbacks
int Shell::up_arrow_key_function(int count, int key) {
    command_history.go_up_history();
    return 0;
}

int Shell::down_arrow_key_function(int count, int key) {
    command_history.go_down_history();
    return 0;
}

Shell::Shell() {
    // up and down arrow key bindings
    rl_bind_keyseq("\033[A", up_arrow_key_function);
    rl_bind_keyseq("\033[B", down_arrow_key_function);

    // CTRL-P and CTRL-N bindings
    rl_bind_key(16, up_arrow_key_function);
    rl_bind_key(14, down_arrow_key_function);

    while (true) {
        char* input = readline("luna $ ");

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
        user_input = input;

        if (!user_input.empty() && user_input[0] != ' ') {
            vector<string> tokens = tokenize();
            parseUserInput(tokens);
        }

        free(input);
    }
}

Shell::~Shell() {
    /* Clean up resources */
}

/**
 * @brief  Tokenizes user input string
 *
 * This function takes in the user input string and tokenizes by white space.
 *
 * @return vector of tokens for command parsing
 */
vector<string> Shell::tokenize() {
    istringstream iss(user_input);
    vector<string> tokens;
    string token;

    // extraction operator default delimeter is whitespace
    while (iss >> token) {
        tokens.push_back(token);
    }


    size_t tokens_length = tokens.size();
    // if echo command used, text enclosed in quotations is treated as one token
    if (tokens[0] == "echo" && tokens_length > 1 && tokens[1][0] == '"') {
        //second is an edge case for when user goes to new line right after first quotation
        while (tokens[tokens_length - 1].back() != '"' || tokens[1].size() == 1) {
            cout << ":( > ";
            string additional;
            getline(cin, additional);
            user_input = user_input + "\n" + additional;
            if (additional.back() == '"') {
                break;
            }
        }

        size_t echo_input_start = user_input.find("\"");
        /* Gets substring from first quotation, upto last quotation.
        Second parameter is no. of characters to include in substring towards the end */
        tokens = {"echo", user_input.substr(echo_input_start + 1, user_input.size() - echo_input_start - 2)};
    }
    return tokens;
}

/**
 * @brief  Parses command and instantiates corresponding object
 *
 * This function takes in the user input tokens and looks at the first command.
 * Afterwards it will instantiate the appropriate Command object and call it's method
 * for the command to execute.
 *
 * @param tokens: tokenized user input string
 *
 * @return vector of tokens for command parsing
 */
void Shell::parseUserInput(const vector<string>& tokens) {
    string command = tokens[0];
    if (command == "echo") {
        EchoCommand echo(tokens);
        echo.echo_fn();
        command_history.insert_command(echo);
        cout << echo.result << endl;
    } else if (command == "pwd") {
        PwdCommand pwd(tokens);
        pwd.pwd_fn();
        command_history.insert_command(pwd);
        cout << pwd.result;
    } else if (command == "cd") {
        CdCommand cd(tokens);
        cd.cd_fn();
        command_history.insert_command(cd);
        cout << cd.result;
    } else if (command == "mkdir") {
        MkDirCommand mkdir(tokens);
        mkdir.mkdir_fn();
        command_history.insert_command(mkdir);
        cout << mkdir.result;
    } else if (command == "rm" || tokens[0] == "rmdir") {
        RmCommand rm(tokens);
        rm.rm_fn();
        command_history.insert_command(rm);
        cout << rm.result;
    } else if (command == "ls") {
        LsCommand ls(tokens);
        ls.ls_fn();
        command_history.insert_command(ls);
        cout << ls.result;
    } else if (command == "mv") {
        MvCommand mv(tokens);
        mv.mv_fn();
        command_history.insert_command(mv);
        cout << mv.result;
    } else if (command == "cat") {
        CatCommand cat(tokens);
        cat.cat_fn();
        command_history.insert_command(cat);
        cout << cat.result;
    } else if (command == "wc") {
        WcCommand wc(tokens);
        command_history.insert_command(wc);
        cout << wc.result;
    } else {
        cout << "luna.sh: command not found: " << tokens[0] << endl;
    }
}
