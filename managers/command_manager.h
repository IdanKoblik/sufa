#ifndef SUFA_COMMAND_MANAGER_H
#define SUFA_COMMAND_MANAGER_H
#include <map>
#include <string>
#include <vector>

class Command;

class CommandManager {
private:
    std::map<std::string, Command*> commands;
    std::map<std::string, std::string> commandsCache;

    CommandManager() = default;
    ~CommandManager() = default;

public:
    static CommandManager& getInstance() {
        static CommandManager instance;
        return instance;
    }

    CommandManager(const CommandManager&) = delete;
    CommandManager& operator=(const CommandManager&) = delete;

    void addCommand(Command *cmd);
    void removeCommand(const std::string& cmd);
    void cleanupCommands();
    Command *getCommand(const std::string& cmd) const;
    const std::vector<std::string> getBuiltinCommands() const;

    void addCommandCache(const std::string& cmd, const std::string& path);
    void removeCommandCache(const std::string& cmd);
    void cleanupCommandCache();
    const std::string& getCommandCache(const std::string& cmd) const;
};

#endif //SUFA_COMMAND_MANAGER_H