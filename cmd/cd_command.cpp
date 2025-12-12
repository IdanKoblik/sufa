#include "cd_command.h"
#include <iostream>
#include <filesystem>
#include <unistd.h>

#include "../home.h"

void CdCommand::exec(std::vector<std::string> &args) const {
    try {
        Command::exec(args);
    } catch (const std::runtime_error &e) {
        std::cerr << "Base command error: " << e.what() << std::endl;
    }

    if (args.empty())
        return;

    const char *target;
    if (args.size() == 1) {
        target = std::getenv("HOME");
        if (!target) {
            target = "/";
        }
    } else {
        target = args[1].c_str();
        homeExpand(args);
    }

    if (chdir(target) != 0) {
        std::cerr << "cd: " << target << ": No such file or directory" << std::endl;
    }
}
