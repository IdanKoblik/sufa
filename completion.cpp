#include <cstdio>
#include <readline/readline.h>
#include <readline/history.h>

#include "completion.h"
#include <vector>
#include "managers/command_manager.h"

CompletionEngine completion;

char* completionGenerator(const char* text, int state) {
    static std::vector<std::string> matches;
    static size_t index = 0;

    if (!state) {
        std::string line(rl_line_buffer, rl_point);
        bool isFirstWord = line.find(' ') == std::string::npos;
        matches = completion.complete(text, isFirstWord);
        index = 0;
    }

    if (index >= matches.size()) return nullptr;
    return strdup(matches[index++].c_str());
}


char** completer(const char* text, int start, int end) {
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, completionGenerator);
}

void initCompletion() {
    CommandManager& commandManager = CommandManager::getInstance();

    completion.loadBuiltins(commandManager.getBuiltinCommands());

    completion.loadPathExecutables();
    rl_attempted_completion_function = completer;
}


std::vector<std::string> CompletionEngine::complete(const std::string& text, bool isFirstWord) {
    std::vector<std::string> matches;

    if (isFirstWord) {
        return trie.complete(text);
    }

    std::filesystem::path p(text.empty() ? "." : text);
    std::filesystem::path dir = p.parent_path().empty() ? "." : p.parent_path();
    std::string base = p.filename();

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        std::string name = entry.path().filename().string();
        if (name.rfind(base, 0) == 0) {
            std::string match = (dir / name).string();
            if (entry.is_directory()) match += '/';
            matches.push_back(match);
        }
    }

    return matches;
}