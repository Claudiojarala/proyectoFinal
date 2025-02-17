#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include <string>
#include "CuckooHash.h"
#include "Trie.h"

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
