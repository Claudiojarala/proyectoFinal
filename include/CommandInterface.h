#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include "Trie.h"
#include "CuckooHash.h"

using namespace std;

class CommandInterface {
private:
    Trie trie;
    CuckooHash dbStore;

public:
    CommandInterface();
    void processCommand(const string &input);
};

#endif // COMMANDINTERFACE_H
