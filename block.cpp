#include "include/class/block.h"

Block::Block()
{
    //header
    prev_block_hash = hash("default");
    timestamp = time(0);
    version = "0.1";
    merkle_root_hash = hash("default");
    nonce = 0;

    //idk what happens with uninicialized transactions
}

Block::Block(std::vector<Transaction *> included_transactions, std::string prev_block_hash)
{
    this->prev_block_hash = prev_block_hash;
    timestamp = time(0);
    version = "0.1";
    this->included_transactions = included_transactions;
    setTransID();
    merkle_root_hash = merkleRoot();
    findTheRightNonce();
}

std::string Block::merkleRoot()
{
    std::vector<std::string> temp = transactionIDs;
    std::vector<std::string> temp2;
    while (temp.size() > 1)
    {
        if (temp.size() & 1) // checks if size is even, if its not, adds the same element to the back
            temp.push_back(temp.back());

        for (int i = 0; i < temp.size(); i += 2)          // loops through the vector of hashes of previuos layer
            temp2.push_back(hash(temp[i] + temp[i + 1])); // push back hash of two nearby elements

        temp = temp2;
        temp2.clear();
    }
    return temp[0];
}

void Block::findTheRightNonce()
{
    std::cout << "Mining.....................................";
    std::string str = hash(blockToString(*this));
    std::string str2(difficulty_target, '0');
    unsigned long long count = 0; // count for stopping the transaction, lol

    srand(time(NULL));

    while (str.substr(0, difficulty_target) != str2) // while not found??????
    {
        nonce = rand();
        str = hash(blockToString(*this));
        if (count++ > 10000)
            throw "\nOh no you need to stop";
    }

    std::cout << "\nI FOUND THE BLOCK!: " << str << std::endl;
}

void Block::setTransID()
{
    for (auto it = included_transactions.begin(); it != included_transactions.end(); ++it)
        transactionIDs.push_back((*it)->ID);
}

std::string blockToString(Block block)
{
    std::stringstream ss;
    ss << block.prev_block_hash << block.timestamp
       << block.version << block.merkle_root_hash
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
       << "\nMerkle root hash: " << block.merkle_root_hash
       << "\nNonce: " << block.nonce
       << "\nDifficulty target: " << std::to_string(block.difficulty_target);

    std::string str = ss.str();
    return ss.str();
}

std::string getBlockInfoTrans(Block block)
{
    std::stringstream ss;
    ss << "-------------------\n"
       << std::setw(20) << std::left << "Hash of prev block: " << block.prev_block_hash
       << "\nTimestamp: " << block.timestamp
       << ", version: " << block.version
       << "\nMerkle root hash: " << block.merkle_root_hash
       << "\nNonce: " << block.nonce
       << "\nDifficulty target: " << std::to_string(block.difficulty_target);

    // now move on to stringing the transactions ;)
    for (auto it = block.included_transactions.begin(); it != block.included_transactions.end(); ++it)
        ss << getTransactionInfo(**it) << "\n";

    std::string str = ss.str();
    return ss.str();
}