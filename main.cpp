#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#include <readline/readline.h>
#include <readline/history.h>

#include "args.h"
#include "home.h"
#include "signal.h"
#include "completion.h"
#include "cmd/cd_command.h"
#include "cmd/cmd_cache.h"
#include "cmd/command.h"
#include "managers/command_manager.h"

const std::string PROMPT = "$ ";
const std::string EXIT_COMMAND = "exit";

CommandManager& commandManager = CommandManager::getInstance();
void initBuiltinCommand();

int main() {
    initBuiltinCommand();
    initCompletion();

    std::signal(SIGINT, signalHandler);
    std::signal(SIGHUP, signalHandler);
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGQUIT, signalHandler);

    std::string input;
    std::string path = getenv("PATH");

    while (true) {
        char* raw = readline(PROMPT.c_str());
        if (!raw) {
            std::cout << std::endl;
            break;
        }

        std::string input(raw);
        free(raw);

        if (input.empty()) {
            continue;
        }

        add_history(input.c_str());
        if (input == EXIT_COMMAND) {
            exit(0);
        }

        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string token;

        while (iss >> token) {
            args.push_back(token);
        }

        if (args.empty()) {
            continue;
        }

        homeExpand(args);
        std::string cmd = args[0];

        if (commandManager.getCommand(cmd)) {
            commandManager.getCommand(cmd)->exec(args);
            continue;
        }

        if (commandManager.getCommandCache(cmd).empty()) {
            std::stringstream ss(path);
            std::string dir;

            while (std::getline(ss, dir, ':')) {
                std::filesystem::path fullPath = dir + '/' + cmd;
                if (std::filesystem::exists(fullPath) &&
                    access(fullPath.c_str(), X_OK) == 0)
                {
                    commandManager.addCommandCache(cmd, fullPath.c_str());
                    break;
                }
            }

            if (commandManager.getCommandCache(cmd).empty()) {
                std::cout << cmd << ": command not found.\n";
                continue;
            }
        }

        if (access(commandManager.getCommandCache(cmd).c_str(), X_OK) != 0) {
            std::cout << cmd << ": command not executable.\n";
            continue;
        }

        const std::vector<char*> argv = makeArgv(args);
        pid_t pid = fork();
        if (pid == 0) {
            execvp(commandManager.getCommandCache(cmd).c_str(), argv.data());
            perror("execvp");
            exit(1);
        }

        if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork");
        }
    }

    return 0;
}

void initBuiltinCommand() {
    commandManager.addCommand(new CdCommand());
    commandManager.addCommand(new CmdCacheCommand());
}