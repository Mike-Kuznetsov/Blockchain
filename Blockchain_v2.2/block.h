#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"

class Block {
    public:
    int number;
    int minerID;
    Transaction transactions[100];
    int balances[9];
    int transactionCount[9];
    int i;
    std::string hash;
    std::string prevHash;
    std::string data;
    int nonce;
    void setContent(int setNumber, std::string setPrevHash, int setBalances[], int setTransCount[]);
    void addTransaction(Transaction transaction);
    std::string hashFunc();
};

#endif
