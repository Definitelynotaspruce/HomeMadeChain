#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction
{
    public:
    std::string ID;
    std::string sender_public_key;
    std::string reciever_public_key;
    int sum;

    Transaction();
    Transaction(std::string, std::string);
    Transaction(std::string, std::string, int);

};

#endif