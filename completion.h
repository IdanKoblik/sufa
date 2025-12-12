#ifndef SUFA_COMPLETION_H
#define SUFA_COMPLETION_H

#include <filesystem>
#include <unistd.h>
#include <vector>

#include "structs/trie.h"

class CompletionEngine {
private:
    Trie trie;

public:
    CompletionEngine() {}

    void loadBuiltins(const std::vector<std::string>& cmds) {
        for (const auto& c : cmds) trie.insert(c);
    }

    void loadPathExecutables() {
        std::string path = getenv("PATH");
        std::stringstream ss(path);
        std::string dir;

        while (std::getline(ss, dir, ':')) {
            if (!std::filesystem::exists(dir)) continue;
            for (const auto& entry : std::filesystem::directory_iterator(dir)) {
                if (entry.is_regular_file() &&
                    access(entry.path().c_str(), X_OK) == 0)
                {
                    trie.insert(entry.path().filename().string());
                }
            }
        }
    }

    std::vector<std::string> complete(const std::string& text, bool isFirstWord);
};

void initCompletion();

#endif //SUFA_COMPLETION_H