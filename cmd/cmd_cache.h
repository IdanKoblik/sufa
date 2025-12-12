#ifndef SUFA_CLEAR_CMD_CACHE_H
#define SUFA_CLEAR_CMD_CACHE_H
#include "command.h"

namespace CmdCache {
    const std::string NAME = "cmd-cache";
    const std::string CLEAR_FLAG = "clear";
}

class CmdCacheCommand : public Command {
public:
    CmdCacheCommand() : Command(CmdCache::NAME, {CmdCache::CLEAR_FLAG}) {}
    ~CmdCacheCommand() override = default;

    void exec(std::vector<std::string> &args) const override;
};

#endif //SUFA_CLEAR_CMD_CACHE_H