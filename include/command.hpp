#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
using namespace std;
namespace fs = filesystem;

class Command {
protected:
    string current_path;
    size_t num_tokens;
    void set_command_options(const string& options_token);
    void options_handler();
    void disable_all_options();

    // boolean to support disabling all the options if any is explicitly filtered in user input
    bool disable_all_options_if_explicit_found = true;

    // boolean flag to check if an invalid option is found, where command functionality terminates
    bool invalid_option_found = false;

public:
    unordered_map<char, bool> command_options;
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

class WcCommand : public Command {
private:
    void append_count_to_result(int current_word_count, int current_line_count, int current_character_count);
public:
    WcCommand(const vector<string>& new_tokens);
    void wc_fn();
};
