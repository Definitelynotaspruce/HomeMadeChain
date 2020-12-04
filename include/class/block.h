#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "../headers/hash.h"

#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <bitcoin/bitcoin.hpp>

class Block
{
public:
    Block *prev = nullptr;
    //header
    std::string prev_block_hash;
    time_t timestamp;
    std::string version;
    std::string merkle_root_hash;
    int nonce;
    int difficulty_target = 3;

    //transactions
    std::vector<Transaction *> included_transactions;
    std::vector<std::string> transactionIDs;

    Block();
    Block(std::vector<Transaction *>, std::string);
    Block(std::vector<Transaction *>, std::string, bool);

    void findTheRightNonce();
    void setTransID();
    std::string merkleRoot();
    bc::hash_list convertToTx_list(std::vector<std::string>&);
    bc::hash_digest create_merkle(bc::hash_list &);

    friend std::string blockToString(Block);
    friend std::string includedTransToString(Block);
    friend std::string getBlockInfo(Block);
    friend std::string getBlockInfoTrans(Block);
};

#endif