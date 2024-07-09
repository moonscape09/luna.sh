#include <string>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

class Command {
protected:
    string current_path;
    size_t num_tokens;
public:
    vector<string> command_tokens;
    string result;
    Command(const vector<string>& new_tokens);
    ~Command();
};

class EchoCommand : public Command {
public:
    EchoCommand(const vector<string>& new_tokens) : Command (new_tokens) {};
    void echo_fn();
};

class PwdCommand : public Command {
public:
    PwdCommand(const vector<string>& new_tokens) : Command (new_tokens) {};
    void pwd_fn();
};

class CdCommand : public Command {
public:
    CdCommand(const vector<string>& new_tokens) : Command (new_tokens) {};
    void cd_fn();
};

class MkDirCommand : public Command {
public:
    MkDirCommand(const vector<string>& new_tokens) : Command (new_tokens) {};
    void mkdir_fn();
};

class RmCommand : public Command {
private:
    bool is_rmdir;
public:
    RmCommand(const vector<string>& new_tokens) : Command (new_tokens) {
        is_rmdir = new_tokens[0] == "rmdir" ? true : false;
    };
    void rm_fn();
};

class LsCommand : public Command {
public:
    LsCommand(const vector<string>& new_tokens) : Command (new_tokens) {};
    void ls_fn();
};

class MvCommand : public Command {
public:
    MvCommand(const vector<string>& new_tokens) : Command (new_tokens) {};
    void mv_fn();
};

class CatCommand : public Command {
public:
    CatCommand(const vector<string>& new_tokens) : Command (new_tokens) {};
    void cat_fn();
};
