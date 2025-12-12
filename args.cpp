#include "args.h"

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