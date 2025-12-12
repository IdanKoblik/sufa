#include "cmd_cache.h"

#include <iostream>

#include "../managers/command_manager.h"

void CmdCacheCommand::exec(std::vector<std::string> &args) const {
    if (args.empty()) {
        std::cerr << "Missing args" << std::endl;
        return;
    }

    try {
        Command::exec(args);
    } catch (const std::runtime_error &e) {
        std::cerr << "Base command error: " << e.what() << std::endl;
    }

    CommandManager& manager = CommandManager::getInstance();
    if (findFlag(CmdCache::CLEAR_FLAG, args)) {
        std::cout << "Clearing command cache..." << std::endl;
        manager.cleanupCommandCache();
        std::cout << "Done!" << std::endl;
    }
}
