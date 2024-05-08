#include <string>
#include <vector>
using namespace std;
class Command
{
private:
    vector<string> command_tokens;
    vector<string> tokenize(string user_input);
public:
    Command(string new_command);
    ~Command();
};