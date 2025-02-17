#include "Trie.h"
#include <iostream>

TrieNode::TrieNode() : isEnd(false) {}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    clear(root);
}

void Trie::clear(TrieNode* node) {
    for (auto &p : node->children) {
        clear(p.second);
    }
    delete node;
}

void Trie::insert(const std::string &word) {
    TrieNode* node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end())
            node->children[c] = new TrieNode();
        node = node->children[c];
    }
    node->isEnd = true;
    node->command = word;
}

bool Trie::search(const std::string &word) {
    TrieNode* node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end())
            return false;
        node = node->children[c];
    }
    return node->isEnd;
}

std::string Trie::suggest(const std::string &prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        if (node->children.find(c) == node->children.end())
            return ""; // No hay sugerencias
        node = node->children[c];
    }
    return findCommand(node);
}

std::string Trie::findCommand(TrieNode* node) {
    if (node->isEnd) {
        return node->command; // Retorna el comando si es final.
    }
    for (auto &p : node->children) {
        std::string result = findCommand(p.second);
        if (!result.empty()) {
            return result; // Retorna el primer comando encontrado.
        }
    }
    return ""; // No se encontró ningún comando.
}
