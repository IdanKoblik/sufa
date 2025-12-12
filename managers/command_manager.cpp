#include "command_manager.h"
#include <algorithm>

#include "../cmd/command.h"

void CommandManager::addCommand(Command *cmd) {
    if (!cmd)
        return;

    const std::string name = cmd->getName();
    commands[name] = cmd;
}

void CommandManager::removeCommand(const std::string& cmd) {
    auto it = commands.find(cmd);
    if (it != commands.end()) {
        delete it->second;
        commands.erase(it);
    }
}

void CommandManager::cleanupCommands() {
    for (auto& [name, cmd] : commands) {
        delete cmd;
    }

    commands.clear();
}

const std::vector<std::string> CommandManager::getBuiltinCommands() const {
    std::vector<std::string> result;
    result.reserve(commands.size());

    for (const auto& entry : commands) {
        result.push_back(entry.first);
    }

    return result;
}

Command* CommandManager::getCommand(const std::string& cmd) const {
    auto it = commands.find(cmd);
    if (it != commands.end()) {
        return it->second;
    }
    return nullptr;
}

void CommandManager::addCommandCache(const std::string& cmd, const std::string& path) {
    commandsCache[cmd] = path;
}

void CommandManager::removeCommandCache(const std::string& cmd) {
    auto it = commandsCache.find(cmd);
    if (it != commandsCache.end()) {
        commandsCache.erase(it);
    }
}

void CommandManager::cleanupCommandCache() {
    commandsCache.clear();
}

const std::string& CommandManager::getCommandCache(const std::string& cmd) const {
    auto it = commandsCache.find(cmd);
    if (it != commandsCache.end()) {
        return it->second;
    }

    static const std::string emptyStr;
    return emptyStr;
}
