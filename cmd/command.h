#ifndef SUFA_COMMAND_H
#define SUFA_COMMAND_H

#include <string>
#include <vector>

class Command {
private:
    const std::string name;
    const std::vector<std::string> flags;

public:
    Command(const std::string &name, const std::vector<std::string> &flags);
    virtual ~Command() = default;

    virtual void exec(std::vector<std::string> &args) const;

    const std::string& getName() const;

    std::vector<std::string> getInvalidFlags(const std::vector<std::string>& args) const;
    std::string getFlagValue(const std::string& flag, const std::vector<std::string>& args) const;
    bool findFlag(const std::string& flag, const std::vector<std::string>& args) const;
};

#endif // SUFA_COMMAND_H