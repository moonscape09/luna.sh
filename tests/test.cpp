#include "../include/command.hpp"
#include "../include/test.hpp"
#include <string>
#include <iostream>

void Test::assert_command(const string& expected, const string& actual, const string& test_name) {
    if (expected.compare(actual) == 0) number_of_tests_passed ++;
    else cout << test_name + ": failed\nExpected: " + expected + "\nActual: " + actual << endl;
}
Test::Test() {
    // create objects
    string fullpath;
    string repo_path = fs::current_path();

    /* Echo tests */

    // basic echo: `echo hello world`
    EchoCommand test_echo({"echo", "hello", "world"});
    test_echo.echo_fn();
    assert_command("hello world ", test_echo.result, "Basic echo");

    // empty echo: `echo`
    test_echo = EchoCommand({"echo"});
    test_echo.echo_fn();
    assert_command("", test_echo.result, "Empty echo");

    /* Pwd tests */

    // basic pwd: `pwd`
    PwdCommand test_pwd({"pwd"});
    test_pwd.pwd_fn();
    fullpath = fs::current_path();
    size_t rootdir = fullpath.find("moon.sh");
    if (!test_pwd.result.find(fullpath.substr(rootdir))) cout << "Basic pwd: failed.\n" << "Expected: " << fullpath << "\nActual: " << test_pwd.result << endl;
    else number_of_tests_passed ++;

    // pwd with parameters: `pwd no!`
    test_pwd = PwdCommand({"pwd", "no!"});
    test_pwd.pwd_fn();
    assert_command("pwd: Only write pwd!\n", test_pwd.result, "pwd with parameters");

    /* Cd tests */

    // empty cd: `cd`
    CdCommand test_cd({"cd"});
    test_cd.cd_fn();
    fullpath = fs::current_path();
    assert_command(getenv("HOME"), fullpath, "Empty cd");

    fs::current_path(repo_path);

    // cd with multiple parameters: `cd dir1 dir2`
    test_cd = CdCommand({"cd", "dir1", "dir2"});
    test_cd.cd_fn();
    assert_command("cd: Too many arguments, only write one directory!\n", test_cd.result, "cd with multiple parameters");

    // cd to directory: `cd ../tests`
    test_cd = CdCommand({"cd", "../tests"});
    test_cd.cd_fn();
    fullpath = fs::current_path();
    rootdir = fullpath.find("tests");
    if (rootdir == string::npos) cout << "cd to directory: failed" << endl;
    else number_of_tests_passed ++;

    // cd on non-existent item: `cd nonexistent`
    test_cd = CdCommand({"cd", "nonexistent"});
    test_cd.cd_fn();
    fullpath = fs::current_path();
    assert_command("cd: No such file or directory: nonexistent\n", test_cd.result, "cd on non-existent directory");

    fs::current_path(repo_path);

    // cd on file: `cd luna.sh`
    test_cd = CdCommand({"cd", "luna.sh"});
    test_cd.cd_fn();
    fullpath = fs::current_path();
    assert_command("cd: Not a directory: luna.sh\n", test_cd.result, "cd on file");

    /* MkDir tests */

    // empty mkdir: `mkdir`
    MkDirCommand test_mkdir = MkDirCommand({"mkdir"});
    test_mkdir.mkdir_fn();
    assert_command("mkdir: Please provide a directory name.\n", test_mkdir.result, "mkdir with no arguments");

    // basic mkdir: `mkdir hello world`
    test_mkdir = MkDirCommand({"mkdir", "hello", "world"});
    test_mkdir.mkdir_fn();
    if (!fs::exists("hello") && fs::exists("world")) cout << "basic mkdir failed" << endl;
    else number_of_tests_passed ++;

    // mkdir on existing directory: `mkdir hello`
    test_mkdir = MkDirCommand({"mkdir", "hello"});
    test_mkdir.mkdir_fn();
    assert_command("mkdir: hello already exists!\n", test_mkdir.result, "mkdir on existing directory");

    /* Rm/Rmdir tests */

    // empty rm: `rm`
    RmCommand test_rm({"rm"});
    test_rm.rm_fn();
    assert_command("rm: Please specify a file\n", test_rm.result, "rm with no arguments");

    // empty rmdir: `rmdir`
    test_rm = RmCommand({"rmdir"});
    test_rm.rm_fn();
    assert_command("rmdir: Please specify a directory\n", test_rm.result, "rmdir with no arguments");

    // rm on nonexistent item: `rm nonexistent`
    test_rm = RmCommand({"rm", "nonexistent"});
    test_rm.rm_fn();
    assert_command("rm: file doesn't exist!\n", test_rm.result, "rm with nonexistent file");

    // rmdir on nonexistent item: `rmdir nonexistent`
    test_rm = RmCommand({"rmdir", "nonexistent"});
    test_rm.rm_fn();
    assert_command("rmdir: directory doesn't exist!\n", test_rm.result, "rm with nonexistent directory");

    // rm on current directory: `rm .`
    test_rm = RmCommand({"rm", "."});
    test_rm.rm_fn();
    assert_command("rm: Invalid argument\n", test_rm.result, "rm on current directory");

    // rmdir on current directory: `rmdir .`
    test_rm = RmCommand({"rmdir", "."});
    test_rm.rm_fn();
    assert_command("rmdir: Invalid argument\n", test_rm.result, "rmdir on current directory");

    // rm on directory: `rm hello`
    test_rm = RmCommand({"rm", "hello"});
    test_rm.rm_fn();
    assert_command("rm: hello is a directory\n", test_rm.result, "rm on directory");

    // rmdir on file: `rmdir command.cpp`
    test_rm = RmCommand({"rmdir", "command.cpp"});
    test_rm.rm_fn();
    assert_command("rmdir: command.cpp is not a directory\n", test_rm.result, "rmdir on file");

    // rmdir on directories: `rmdir hello world`
    test_rm = RmCommand({"rmdir", "hello", "world"});
    test_rm.rm_fn();
    if (fs::exists("hello") || fs::exists("world")) cout << "rmdir on directories: failed" << endl;
    else number_of_tests_passed ++;

    // rm on files: `rm command.cpp command.hpp`
    test_rm = RmCommand({"rm", "command.cpp", "command.hpp"});
    test_rm.rm_fn();
    if (fs::exists("command.cpp") || fs::exists("command.hpp")) cout << "rm on files: failed" << endl;
    else number_of_tests_passed ++;

    // rmdir on non-empty directory: `rm ../tests`
    test_rm = RmCommand({"rmdir", "../tests"});
    test_rm.rm_fn();
    assert_command("rmdir: Directory not empty: ../tests\n", test_rm.result, "rmdir on non-empty directory");

    /* Ls tests */

    // basic ls: `ls`
    LsCommand test_ls({"ls"});
    test_ls.ls_fn();
    assert_command("command-history.cpp    luna.cpp    luna.sh    mv_test_dir    commands    shell.cpp    \n", test_ls.result, "basic ls");

    // ls on file: `ls luna.cpp`
    test_ls = LsCommand({"ls", "luna.cpp"});
    test_ls.ls_fn();
    assert_command("luna.cpp    \n", test_ls.result, "ls on file");

    // ls on explicit directory: `ls ../tests`
    test_ls = LsCommand({"ls", "../include"});
    test_ls.ls_fn();
    assert_command("../include/: \nshell.hpp    test.hpp    command.hpp    command-history.hpp    \n", test_ls.result, "ls on directory");

    // ls on multiple directories: `ls ../tests .`
    test_ls = LsCommand({"ls", "../include", "."});
    test_ls.ls_fn();
    assert_command("../include/: \nshell.hpp    test.hpp    command.hpp    command-history.hpp    \n\n./: \ncommand-history.cpp    luna.cpp    luna.sh    mv_test_dir    commands    shell.cpp    \n",
                        test_ls.result, "ls on directories");

    // ls on files and directories: `ls luna.cpp ../tests . luna.sh`
    test_ls = LsCommand({"ls", "luna.cpp", "../include", ".", "luna.sh"});
    test_ls.ls_fn();
    assert_command("luna.cpp    luna.sh    \n\n../include/: \nshell.hpp    test.hpp    command.hpp    command-history.hpp    \n\n./: \ncommand-history.cpp    luna.cpp    luna.sh    mv_test_dir    commands    shell.cpp    \n",
                        test_ls.result, "ls on files and directories");

    // ls on nonexistent item: `ls nonexistent`
    test_ls = LsCommand({"ls", "nonexistent"});
    test_ls.ls_fn();
    assert_command("ls: No such file or directory: nonexistent\n", test_ls.result, "ls on nonexistent item");

    // ls on nonexistent and existent item without termination: `ls nonexistent ../tests`
    test_ls = LsCommand({"ls", "nonexistent", "../include"});
    test_ls.ls_fn();
    assert_command("ls: No such file or directory: nonexistent\n../include/: \nshell.hpp    test.hpp    command.hpp    command-history.hpp    \n",
                        test_ls.result, "ls on nonexistent and existent items without termination");

    /* Mv tests */

    // mv with insufficient arguments: `mv luna.sh`
    MvCommand test_mv({"mv", "luna.sh"});
    test_mv.mv_fn();
    assert_command("mv: Please provide a source and target!\n", test_mv.result, "mv on less than 3 items");

    // mv on multiple files to non-directory item: `mv luna.sh luna.cpp command.cpp`
    test_mv = MvCommand({"mv", "luna.sh", "luna.cpp", "command.cpp"});
    test_mv.mv_fn();
    assert_command("mv: command.cpp is not a directory\n", test_mv.result, "mv on multiple files to non-directory target");

    // mv on files to a target directory: `mv luna.sh luna.cpp ../tests`
    test_mv = MvCommand({"mv", "luna.sh", "luna.cpp", "../tests"});
    test_mv.mv_fn();
    if (!fs::exists("../tests/luna.sh") && !fs::exists("../tests/luna.cpp")) cout << "mv: moving files to directory: failed" << endl;
    else number_of_tests_passed ++;

    // mv a directory to a file: `mv ../tests/shell.cpp`
    test_mv = MvCommand({"mv", "../tests", "shell.cpp"});
    test_mv.mv_fn();
    assert_command("mv: cannot rename a directory to name of an existing file: shell.cpp\n", test_mv.result, "mv on directory to a file");

    // mv usage to rename a file: `mv shell.cpp new_name.cpp`
    test_mv = MvCommand({"mv", "shell.cpp", "new_name.cpp"});
    test_mv.mv_fn();
    if (!fs::exists("new_name.cpp") && fs::exists("shell.cpp")) cout << "mv: renaming a file: failed" << endl;
    else number_of_tests_passed ++;

    // mv a directory to another directory `mv mv_test_dir ..`
    test_mv = MvCommand({"mv", "mv_test_dir", ".."});
    test_mv.mv_fn();
    if (!fs::exists("../mv_test_dir")) cout << "mv: moving one directory to another: failed" << endl;
    else number_of_tests_passed ++;

    /* Cat tests */

    // empty cat: `cat`
    CatCommand test_cat({"cat"});
    test_cat.cat_fn();
    assert_command("cat: Not supported yet.\n", test_cat.result, "empty cat");

    // cat on nonexistent item: `cat nonexistent`
    test_cat = CatCommand({"cat", "nonexistent"});
    test_cat.cat_fn();
    assert_command("cat: No such file: nonexistent\n", test_cat.result, "cat on nonexistent item");

    // cat on directory: `cat ../src`
    test_cat = CatCommand({"cat", "../src"});
    test_cat.cat_fn();
    assert_command("cat: ../src is a directory\n", test_cat.result, "cat on directory");

    // cat on file: `cat ../cat_testing.txt`
    test_cat = CatCommand({"cat", "../cat_testing.txt"});
    test_cat.cat_fn();
    assert_command("../cat_testing.txt: \n\nHello world\n\n", test_cat.result, "cat on a file");

    cout << number_of_tests_passed << "/40 passed" << endl;
}

Test::~Test() {};
