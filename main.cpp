#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>

#include "home.h"
#include "cmd/cd_command.h"
#include "cmd/command.h"

const std::string PROMPT = "$ ";
const std::string EXIT_COMMAND = "exit";

std::map<std::string, Command*> commands;

std::vector<char*> makeArgv(const std::vector<std::string>& args);
std::vector<std::string> sanitizePath(const std::string& rawPath);
void initBuiltinCommand();
void cleanupCommands();
void signalHandler(int signum);

int main() {
    std::signal(SIGINT, signalHandler);
    std::signal(SIGHUP, signalHandler);
    std::signal(SIGTERM, signalHandler);

    atexit(cleanupCommands);
    initBuiltinCommand();

    std::string input;
    std::string path = getenv("PATH");
    std::map<std::string, std::string> commandCache;

    std::cout << PROMPT;
    while (std::getline(std::cin, input)) {
        if (input == EXIT_COMMAND) {
            exit(1);
        }

        if (input.empty()) {
            std::cout << PROMPT;
            continue;
        }

        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string token;

        while (iss >> token) {
            if (!token.empty())
                args.push_back(token);
        }

        if (args.empty()) {
            std::cout << PROMPT;
            continue;
        }

        homeExpand(args);
        std::string cmd = args[0];
        if (commands[cmd]) {
            commands[cmd]->exec(args);
            std::cout << PROMPT;
            continue;
        }

        if (commandCache.find(cmd) == commandCache.end()) {
            std::stringstream ss(path);
            std::string dir;

            while (std::getline(ss, dir, ':')) {
                std::filesystem::path fullPath = dir + '/' + cmd;
                if (std::filesystem::exists(fullPath) && access(fullPath.c_str(), X_OK) == 0) {
                    commandCache[cmd] = fullPath.c_str();
                    break;
                }
            }

            if (commandCache.find(cmd) == commandCache.end()) {
                std::cout << cmd << ": command not found." << std::endl;
                std::cout << PROMPT;
                continue;
            }
        }

        if (access(commandCache[cmd].c_str(), X_OK) != 0) {
            std::cout << cmd << ": command not executable." << std::endl;
            std::cout << PROMPT;
            continue;
        }

        const std::vector<char *> argv = makeArgv(args);
        pid_t pid = fork();
        if (pid == 0) {
            execvp(commandCache[cmd].c_str(), argv.data());
            perror("execvp");
            exit(1);
        }

        if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork");
        }

        std::cout << PROMPT;
    }

    return 0;
}

std::vector<char*> makeArgv(const std::vector<std::string>& args) {
    std::vector<char*> argv;
    argv.reserve(args.size() + 1);

    for (const std::string& s : args) {
        char* cp = new char[s.size() + 1];
        std::copy(s.begin(), s.end(), cp);
        cp[s.size()] = '\0';
        argv.push_back(cp);
    }

    argv.push_back(nullptr);
    return argv;
}

std::vector<std::string> sanitizePath(const std::string& rawPath) {
    std::vector<std::string> dirs;
    std::stringstream ss(rawPath);
    std::string dir;

    while (std::getline(ss, dir, ':')) {
        if (dir.empty() || dir == "." || dir[0] != '/')
            continue;

        if (std::filesystem::is_directory(dir))
            dirs.push_back(dir);
    }

    return dirs;
}

void initBuiltinCommand() {
    CdCommand *cd = new CdCommand();
    commands[cd->getName()] = cd;
}

void cleanupCommands() {
    for (auto& [name, cmd] : commands) {
        delete cmd;
    }

    commands.clear();
}

void signalHandler(int signum) {
    cleanupCommands();
    std::exit(signum);
}