#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "class/transaction.h"

class block
{
    public:
    //header
    std::string prev_block_hash;
    std::string timestamp;
    std::string version;
    std::string merkel_root_hash;
    int nonce;
    int difficulty_target;

    //transactions
    std::vector<transaction> included_transactions;

    block();
    block(std::string, std::string);

};

#endif