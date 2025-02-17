#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEnd;
    std::string command;
    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    void clear(TrieNode* node);

public:
    Trie();
    ~Trie();
    void insert(const std::string &word);
    bool search(const std::string &word);
    std::string suggest(const std::string &prefix);

private:
    std::string findCommand(TrieNode* node);
};

#endif // TRIE_H
