#include "command.h"
#include <algorithm>
#include <iostream>

Command::Command(const std::string &name, const std::vector<std::string> &flags) : name(name), flags(flags) {}

void Command::exec(std::vector<std::string> &args) const {
    std::vector<std::string> invalid = getInvalidFlags(args);
    if (!invalid.empty()) {
        std::string msg = "Invalid flags detected: ";
        for (const auto &flag : invalid) {
            msg += flag + " ";
        }
        throw std::runtime_error(msg);
    }
}

const std::string& Command::getName() const {
    return name;
}

std::vector<std::string> Command::getInvalidFlags(const std::vector<std::string>& args) const {
    std::vector<std::string> invalid;
    for (const std::string& arg : args) {
        if (arg.rfind("--", 0) == 0) {
            std::string flagName = arg.substr(2);
            if (std::find(flags.begin(), flags.end(), flagName) == flags.end()) {
                invalid.push_back(arg);
            }
        }
    }
    return invalid;
}

std::string Command::getFlagValue(const std::string& flag, const std::vector<std::string>& args) const {
    std::string target = "--" + flag;
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == target) {
            if (i + 1 < args.size() && args[i + 1].rfind("--", 0) != 0) {
                return args[i + 1];
            }
            return "";
        }
    }
    return "";
}

bool Command::findFlag(const std::string& flag, const std::vector<std::string>& args) const {
    std::string target = "--" + flag;
    return std::find(args.begin(), args.end(), target) != args.end();
}
