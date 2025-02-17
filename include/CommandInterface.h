#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include "Trie.h"
#include "CuckooHash.h"

class CommandInterface {
private:
    Trie trie;
    CuckooHash dbStore;

public:
    CommandInterface();
    void processCommand(const string &input);
};

#endif // COMMANDINTERFACE_H
