#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "../headers/hash.h"

#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
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
    int difficulty_target = 3;

    //transactions
    std::vector<Transaction*> included_transactions;

    Block();
    Block(std::vector<Transaction*>, std::string);
    //Block(std::vector<Transaction>, int);

    void findTheRightNonce();
    friend std::string blockToString(Block);
    friend std::string includedTransToString(Block);
    friend std::string getBlockInfo(Block);
};

#endif