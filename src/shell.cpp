#include <iostream>
#include "shell.hpp"
#include "command.hpp"

Shell::Shell() {
    string command;
    cout << "Welcome to moon.sh!\n";
    while(true) {
        cout << "moon $ ";
        cin >> command;
        /* Gracefully exit the shell */
        if (command == "exit") {
            break;
        }
        Command cmd(command);
    }
}   

Shell::~Shell() {
    /* Clean up resources */
}

