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

class PwdCommand : public Command {
public:
    PwdCommand(vector<string> new_tokens) : Command (new_tokens) {};
    void pwd_fn();
};

class CdCommand : public Command {
public:
    CdCommand(vector<string> new_tokens) : Command (new_tokens) {};
    void cd_fn();
};

class MkDirCommand : public Command {
public:
    MkDirCommand(vector<string> new_tokens) : Command (new_tokens) {};
    void mkdir_fn();
};
