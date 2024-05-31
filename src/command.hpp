#include <string>
#include <vector>
using namespace std;

class Command {
protected:
    vector<string> command_tokens;
    size_t num_tokens;
public:
    string result;
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

class RmCommand : public Command {
private:
    bool is_rmdir;
public:
    RmCommand(vector<string> new_tokens) : Command (new_tokens) {
        is_rmdir = new_tokens[0] == "rmdir" ? true : false;
    };
    void rm_fn();
};

class LsCommand : public Command {
public:
    LsCommand(vector<string> new_tokens) : Command (new_tokens) {};
    void ls_fn();
};

class MvCommand : public Command {
public:
    MvCommand(vector<string> new_tokens) : Command (new_tokens) {};
    void mv_fn();
};

class CatCommand : public Command {
public:
    CatCommand(vector<string> new_tokens) : Command (new_tokens) {};
    void cat_fn();
};
