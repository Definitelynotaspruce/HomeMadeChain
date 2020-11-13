#include "include/class/block.h"

Block::Block()
{
    //header
    prev_block_hash = hash("default");
    timestamp = time(0);
    version = "0.1";
    merkel_root_hash = hash("default");
    nonce = 0;

    //idk what happens with uninicialized transactions
}

Block::Block(std::vector<Transaction *> included_transactions, std::string prev_block_hash)
{
    this->prev_block_hash = prev_block_hash;
    timestamp = time(0);
    version = "0.1";
    merkel_root_hash = hash(includedTransToString(*this));
    this->included_transactions = included_transactions;

    findTheRightNonce();
}

void Block::findTheRightNonce()
{
    std::string str = hash(blockToString(*this));
    std::string str2(difficulty_target, '0');

    srand(time(NULL));

    while (str.substr(0, 3) != str2) // while not found??????
    {
        nonce = rand();
        str = hash(blockToString(*this));
    }

    std::cout << "I FOUND THE BLOCK!: " << str << std::endl;
    //std::cout << getBlockInfo(*this);
}

std::string blockToString(Block block)
{
    std::stringstream ss;
    ss << block.prev_block_hash << block.timestamp
       << block.version << block.merkel_root_hash
       << block.nonce << std::to_string(block.difficulty_target);

    // now move on to stringing the transactions ;)
    for (auto it = block.included_transactions.begin(); it != block.included_transactions.end(); ++it)
        ss << transToString(**it);

    std::string str = ss.str();
    return ss.str();
}

std::string includedTransToString(Block block)
{
    std::stringstream ss;
    for (auto it = block.included_transactions.begin(); it != block.included_transactions.end(); ++it)
        ss << transToString(**it);

    return ss.str();
}

std::string getBlockInfo(Block block)
{
    std::stringstream ss;
    ss << "-------------------\n"
       << std::setw(20) << std::left << "Hash of prev block: " << block.prev_block_hash
       << "\nTimestamp: " << block.timestamp
       << ", version: " << block.version
       << "\nMerkel root hash: " << block.merkel_root_hash
       << "\nNonce: " << block.nonce
       << "\nDifficulty target: " << std::to_string(block.difficulty_target);

    // now move on to stringing the transactions ;)
    for (auto it = block.included_transactions.begin(); it != block.included_transactions.end(); ++it)
        ss << getTransactionInfo(**it) << "\n";

    std::string str = ss.str();
    return ss.str();
}