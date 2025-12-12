#ifndef SUFA_TRIE_H
#define SUFA_TRIE_H

#include <map>
#include <string>
#include <vector>

struct Node {
    bool isEnd = false;
    std::map<char, Node*> children;
};

class Trie {
private:
    Node *root;
    void dfs(Node* node, std::string& prefix, std::vector<std::string>& results);

public:
    Trie() : root(new Node()) {}

    void insert(const std::string& word);
    std::vector<std::string> complete(const std::string& prefix);
};

#endif //SUFA_TRIE_H