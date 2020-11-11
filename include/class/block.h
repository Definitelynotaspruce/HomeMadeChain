#ifndef BLOCK_H
#define BLOCK_H

#include "class/transaction.h"
#include "headers/hash.h"

#include <string>
#include <vector>
#include <ctime>
#include <sstream>


class Block
{
public:
    //header
    std::string prev_block_hash;
    time_t timestamp;
    std::string version;
    std::string merkel_root_hash;
    int nonce;
    int difficulty_target;

    //transactions
    std::vector<Transaction> included_transactions;

    Block();
    Block(std::string, std::string);

    friend std::string blockToString(Block);
};

#endif