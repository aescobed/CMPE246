#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cstdio>

// Function to split a string into tokens based on a delimiter
std::vector<std::string> splitString(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Built-in implementation of "ls"
void builtin_ls(const std::vector<std::string> &args) {
    std::string path = args.size() > 1 ? args[1] : ".";
    DIR *dir = opendir(path.c_str());
    if (dir == nullptr) {
        perror("ls error");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::cout << entry->d_name << "\n";
    }

    closedir(dir);
}

// Built-in implementation of "cd"
void builtin_cd(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        std::cerr << "cd: missing argument\n";
        return;
    }

    if (chdir(args[1].c_str()) != 0) {
        perror("cd error");
    }
}

// Built-in implementation of "mkdir"
void builtin_mkdir(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        std::cerr << "mkdir: missing argument\n";
        return;
    }

    if (mkdir(args[1].c_str(), 0755) != 0) {
        perror("mkdir error");
    }
}

// Built-in implementation of "rm"
void builtin_rm(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        std::cerr << "rm: missing argument\n";
        return;
    }

    if (remove(args[1].c_str()) != 0) {
        perror("rm error");
    }
}

// Built-in implementation of "rmdir"
void builtin_rmdir(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        std::cerr << "rmdir: missing argument\n";
        return;
    }

    if (rmdir(args[1].c_str()) != 0) {
        perror("rmdir error");
    }
}

// Built-in implementation of "pwd"
void builtin_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << cwd << "\n";
    } else {
        perror("pwd error");
    }
}

// Function to execute built-in commands
bool executeBuiltInCommand(const std::vector<std::string> &args) {
    if (args.empty()) {
        return false;
    }

    // Built-in command: exit
    if (args[0] == "exit") { // You can change the "exit" command name here
        std::cout << "Exiting shell...\n";
        exit(0);
    }

    // Built-in command: ls
    if (args[0] == "ls") {
        builtin_ls(args);
        return true;
    }

    // Built-in command: cd
    if (args[0] == "cd") {
        builtin_cd(args);
        return true;
    }

    // Built-in command: mkdir
    if (args[0] == "mkdir") {
        builtin_mkdir(args);
        return true;
    }

    // Built-in command: rm
    if (args[0] == "rm") {
        builtin_rm(args);
        return true;
    }

    // Built-in command: rmdir
    if (args[0] == "rmdir") {
        builtin_rmdir(args);
        return true;
    }

    // Built-in command: pwd
    if (args[0] == "pwd") {
        builtin_pwd();
        return true;
    }

    // Add more custom commands here, for example:
    // if (args[0] == "your_command") {
    //     std::cout << "Your command executed!\n";
    //     return true;
    // }

    return false;
}

// Main function
int main() {
    std::string input;

    while (true) {
        // Display a custom prompt
        std::cout << "myshell> ";
        std::getline(std::cin, input);

        // Split the input into arguments
        std::vector<std::string> args = splitString(input, ' ');

        // Skip empty input
        if (args.empty() || args[0].empty()) {
            continue;
        }

        // Execute built-in commands
        if (executeBuiltInCommand(args)) {
            continue;
        }

        std::cerr << "Command not found: " << args[0] << "\n";
    }

    return 0;
}
