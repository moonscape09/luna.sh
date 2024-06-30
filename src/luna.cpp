#include "../include/shell.hpp"
#include "../include/test.hpp"

int main() {
    if (getenv("LUNA_TESTING_ON")) {
        Test test;
        return 0; // no running shell after tests
    }
    Shell luna;
    return 0;
}
