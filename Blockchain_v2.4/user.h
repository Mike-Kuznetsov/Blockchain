#ifndef USER_H
#define USER_H

#include <string>
#include "block.h"

class User {
    public:
        int lastBlock;
        Block block[10000];
        User();
        std::string *privKey;
        Signature *signature;
        void setPrivKey(std::string *setPrivKey);
        void setBlock(Block receivedBlock);
        //void addData(std::string newData);
        bool check();
        void showChain();
        void showData();
};
#endif
