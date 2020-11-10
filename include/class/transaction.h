#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class transaction
{
    public:
    std::string ID;
    std::string sender_public_key;
    std::string reciever_public_key;
    int sum;

    transaction();
    transaction(std::string, std::string);
    transaction(std::string, std::string, int);

};

#endif