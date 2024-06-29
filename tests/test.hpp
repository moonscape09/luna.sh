#include "../src/command.hpp"
class Test {
protected:
    void assert_command(string expected, string actual, string test_name);
    int number_of_tests_passed = 0;
public:
    Test();
    ~Test();
};
