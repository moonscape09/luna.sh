#include "shell.hpp"
#include "../tests/test.hpp"

int main() {
    if (getenv("LUNA_TESTING_ON")) {
        Test test;
        return 0; // no running shell after tests
    }
    Shell moon;
    return 0;
}
