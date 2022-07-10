#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "signature.h"

class Block {
    public:
    int number;
    int minerID;
    Transaction transactions[100];
    int balances[9];
    int transactionCount[9];
    int i;
    Signature *signature;
    std::string hash;
    std::string prevHash;
    std::string data;
    int nonce;
    void setContent(int setNumber, std::string setPrevHash, int setBalances[], int setTransCount[], Signature *setSignature);
    void addTransaction(Transaction *transaction);
    std::string hashFunc();
};

#endif
