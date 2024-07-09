#include <string>
#include <vector>
#include "../include/command-history.hpp"
using namespace std;
class Shell
{
private:
    string user_input;
    vector<string> tokenize();
    void parseUserInput(const vector<string>& tokens);

    // static member functions used for callbacks
    static int up_arrow_key_function(int count, int key);
    static int down_arrow_key_function(int count, int key);

    // static CommandHistory object in class scope to maintain encapsulation
    static CommandHistory command_history;

public:
    Shell();
    ~Shell();
};
