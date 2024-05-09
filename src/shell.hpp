#include <string>
#include <vector>
using namespace std;
class Shell
{
private:
    string command;
    vector<string> tokenize();
    void parseUserInput(vector<string> tokens);
public:
    Shell();
    ~Shell();
};
