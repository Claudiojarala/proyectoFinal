#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include <string>
#include "CuckooHash.h"
#include "Trie.h"

class CommandInterface {
private:
    Trie trie;
    CuckooHash dbStore;

public:
    CommandInterface();
    void processCommand(const std::string &input);
};

#endif // COMMANDINTERFACE_H
