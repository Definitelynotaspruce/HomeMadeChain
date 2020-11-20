#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../headers/hash.h"
#include "../class/user.h"
#include <random>
#include <string>
#include <sstream>

class Transaction
{
public:
    std::string ID;
    std::string sender_public_key;
    std::string receiver_public_key;  
    User *sender;
    User *receiver;
    int sum;
    bool completed = false;

    Transaction();
    Transaction(User &, User &);
    Transaction(User &, User &, int);

    bool operator==(const Transaction&) const;

    friend bool validateTransaction(Transaction &);
    friend std::string getTransactionInfo(Transaction);
    friend void printDetailedTransactionInfo(Transaction);
    friend std::string transToString(Transaction);
};

#endif