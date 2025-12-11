#pragma once
#include "home.h"

constexpr char HOME_TOKEN = '~';

void homeExpand(std::vector<std::string>& args) {
    const char* home_env = getenv("HOME");
    if (!home_env || home_env[0] != '/')
        return;

    for (std::string &arg : args) {
        if (!arg.empty() && arg[0] == HOME_TOKEN) {
            arg = std::string(home_env) + arg.substr(1);
        }
    }
}