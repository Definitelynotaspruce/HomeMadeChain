#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../headers/hash.h"
#include "../class/user.h"
#include <random>
#include <string>


class Transaction
{
    public:
    std::string ID;
    /* std::string sender_public_key;
    std::string reciever_public_key;  */
    User *sender;
    User *reciever;
    int sum;
    bool completed = false;

    Transaction();
    Transaction(User&, User&);
    Transaction(User&, User&, int);

    friend bool validateTransaction(Transaction);
    friend std::string getTransactionInfo (Transaction);

};

#endif