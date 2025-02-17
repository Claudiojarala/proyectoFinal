#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include "CuckooHash.h"
#include "Trie.h"

class CommandInterface {
private:
    Trie trie;
    CuckooHash dbStore;

public:
    CommandInterface();
    void processCommand(const string &input);
};

#endif // COMMAND_INTERFACE_H
