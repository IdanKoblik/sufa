#include "trie.h"

void Trie::dfs(Node* node, std::string& prefix, std::vector<std::string>& results) {
    if (node->isEnd) results.push_back(prefix);

    for (auto& [ch, child] : node->children) {
        prefix.push_back(ch);
        dfs(child, prefix, results);
        prefix.pop_back();
    }
}

void Trie::insert(const std::string& word) {
    Node* cur = root;
    for (char c : word) {
        if (!cur->children[c]) cur->children[c] = new Node();
        cur = cur->children[c];
    }
    cur->isEnd = true;
}

std::vector<std::string> Trie::complete(const std::string& prefix) {
    Node* cur = root;
    for (char c : prefix) {
        if (!cur->children[c]) return {};
        cur = cur->children[c];
    }

    std::vector<std::string> results;
    std::string tmp = prefix;
    dfs(cur, tmp, results);
    return results;
}