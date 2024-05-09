#include <string>
#include <vector>
using namespace std;

class Command {
protected:
    vector<string> command_tokens;
public:
    Command(vector<string> new_tokens);
    ~Command();
};

class EchoCommand : public Command {
public:
    EchoCommand(vector<string> new_tokens) : Command (new_tokens) {};
    void echo_fn();
};
