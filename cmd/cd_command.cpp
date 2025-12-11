#include "cd_command.h"
#include <iostream>
#include <filesystem>
#include <unistd.h>

void CdCommand::exec(const std::vector<std::string> &args) const {
    const char *target;
    if (args.size() == 1) {
        target = std::getenv("HOME");
        if (!target) {
            target = "/";
        }
    } else {
        target = args[1].c_str();
    }

    if (chdir(target) != 0) {
        std::cerr << "cd: " << target << ": No such file or directory" << std::endl;
    }
}
