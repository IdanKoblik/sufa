#include "signal.h"

#include "managers/command_manager.h"

void signalHandler(int signum) {
    CommandManager &manager = CommandManager::getInstance();
    manager.cleanupCommandCache();
    manager.cleanupCommands();

    std::exit(signum);
}
