#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd;
    string command;
    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    void clear(TrieNode* node);

public:
    Trie();
    ~Trie();
    void insert(const string &word);
    bool search(const string &word);
    string suggest(const string &prefix);

private:
    string findCommand(TrieNode* node);
};

#endif // TRIE_H
