#ifndef SUFA_COMMAND_H
#define SUFA_COMMAND_H

#include <string>
#include <vector>

class Command {
private:
    const std::string name;

public:
    Command(const std::string &name) : name(name) {}
    virtual ~Command() = default;

    virtual void exec(std::vector<std::string> &args) const = 0;
    const std::string& getName() const { return name; }
};


#endif //SUFA_COMMAND_H