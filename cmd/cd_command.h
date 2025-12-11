#ifndef SUFA_CD_COMMAND_H
#define SUFA_CD_COMMAND_H
#include "command.h"

const std::string NAME = "cd";

class CdCommand : public Command {
public:
    CdCommand() : Command(NAME) {}
    ~CdCommand() override = default;

    void exec(std::vector<std::string> &args) const override;
};

#endif //SUFA_CD_COMMAND_H