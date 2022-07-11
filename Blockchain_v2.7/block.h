#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "signature.h"

class Block {
    public:
    int number;
    Transaction transactions[100];
    int balances[8];
    int transactionCount[8];
    int i;
    std::string hash;
    std::string prevHash;
    int nonce;
    void setContent(int setNumber, std::string setPrevHash, int setBalances[], int setTransCount[]);
    void addTransaction(Transaction transaction);
    std::string hashFunc();
};

#endif
