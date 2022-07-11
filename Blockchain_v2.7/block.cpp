#include <iostream>
#include "sha256.h"
#include "block.h"
#include "transaction.h"
#include "signature.h"

using namespace std;

void Block::setContent(int setNumber, string setPrevHash, int setBalances[8], int setTransCount[8]){
    prevHash=setPrevHash;
    number=setNumber;
    nonce=0;
    hash="";
    i=0;
    for (int j=0;j<8;j++){
        balances[j]=setBalances[j];
        transactionCount[j]=setTransCount[j];
    }
}

void Block::addTransaction(Transaction transaction){
    transactions[i]=transaction;
    i++;
}

string Block::hashFunc(){
    string sum="";
    for (int j=0;j<i;j++){
        sum=sum+transactions[i].hashFunc();
    }
    return sha256(to_string(number) + sum + prevHash + to_string(nonce));
}
