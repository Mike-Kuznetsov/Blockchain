#include <iostream>
#include "sha256.h"
#include "block.h"
#include "transaction.h"

using namespace std;

void Block::createBlock(int setNumber, string setPrevHash, int setBalances[8], int setTransCount[8]){
    prevHash=setPrevHash;
    number=setNumber;
    nonce=0;
    hash="";
    lastTransaction=0;
    for (int j=0;j<8;j++){
        balances[j]=setBalances[j];
        transactionCount[j]=setTransCount[j];
    }
}

void Block::addTransaction(Transaction transaction){
    transactions[lastTransaction]=transaction;
    lastTransaction++;
}

string Block::hashFunc(){
    string sum="";
    for (int j=0;j<lastTransaction;j++){
        sum=sum+transactions[j].hashFunc();
    }
    for (int j=0;j<8;j++){
        sum=sum+to_string(balances[j]);
    }
    return sha256(to_string(number) + sum + prevHash + to_string(nonce));
}
