class Test {
protected:
    void assert_command(const string& expected, const string& actual, const string& test_name);
    int number_of_tests_passed = 0;
public:
    Test();
    ~Test();
};
