#include "include/class/transaction.h"
#include "include/headers/hash.h"
#include <random>
#include <string>


transaction::transaction() 
{
    ID = "id";
    sender_public_key = "sender_public_key";
    reciever_public_key = "reciever_public_key";
}

//constructor with random sum
transaction::transaction(std::string senderPK, std::string recieverPK) 
{ 
    sender_public_key = senderPK;
    reciever_public_key = recieverPK;
    sum = rand() % 1000 + 1;
    ID = hash(sender_public_key + reciever_public_key + std::to_string(sum));
}

// constructor with set sum
transaction::transaction(std::string senderPK, std::string recieverPK, int money) 
{ 
    sender_public_key = senderPK;
    reciever_public_key = recieverPK;
    sum = money;
    ID = hash(sender_public_key + reciever_public_key + std::to_string(sum));
}