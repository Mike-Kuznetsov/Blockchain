#include <iostream>
#include "user.h"
#include "signature.h"
#include "transaction.h"
using namespace std;

User user[10];

/*void transaction(int senderID, int receiverID, int value){
    for (int i=0; i<10; i++){
        user[i].balances[senderID]=user[i].balances[senderID]-value;
        user[i].balances[receiverID]=user[i].balances[receiverID]+value;
    }
}*/

int main()
{
    int transactionCount=0;
    Signature sig;
    for (int i=0; i<10; i++){
        user[i].id=i;
        for (int j=0; j<10; j++){
            user[i].balances[j]=1;
        }
        user[i].privKey=sig.keyGen();
        user[i].pubKey=sig.pubKey;
    }
    Transaction transaction;
    transaction.addData(transactionCount, user[1].pubKey, user[2].pubKey, 1);
    transaction.sign(&user[1].privKey);
    for (int i=0; i<10; i++){
        user[i].transaction[transactionCount]=transaction;
    }
    for (int i=0; i<10; i++){
        if (user[i].transaction[transactionCount].check()) cout << "USER " << i << ": Transaction is correct" << endl;
    }
    return 0;
}


