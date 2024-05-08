#include <iostream>
#include <string>
#include "shell.hpp"


Shell::Shell() {
    std::string command;
    std::cout << "Welcome to moon.sh!\n";
    while(true) {
        std::cout << "moon $ ";
        std::cin >> command;
        /* Gracefully exit the shell */
        if (command == "exit") {
            break;
        }
    }
}   

Shell::~Shell() {
    /* Clean up resources */
}

