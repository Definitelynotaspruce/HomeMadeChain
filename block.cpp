#include "include/class/block.h"
#include <bitcoin/bitcoin.hpp>

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

Block::Block(std::vector<Transaction *> included_transactions, std::string prev_block_hash, bool useLibbitcoin)
{
    this->prev_block_hash = prev_block_hash;
    timestamp = time(0);
    version = "0.1";
    this->included_transactions = included_transactions;
    setTransID();
    bc::hash_list tx_hashes = convertToTx_list(transactionIDs);
    const bc::hash_digest merkle_root = create_merkle(tx_hashes);
    merkle_root_hash = bc::encode_base16(merkle_root);
    findTheRightNonce();
}

bc::hash_list Block::convertToTx_list(std::vector<std::string> &transactionIDs)
{
    bc::hash_list tx_hashes = {};
    char str[65];
    std::string transactionID;
    for (auto it = transactionIDs.begin(); it != transactionIDs.end(); ++it)
    {
        (*it).copy(str, 65);
        tx_hashes.push_back(bc::hash_literal(str));
    }
    return tx_hashes;
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

bc::hash_digest Block::create_merkle(bc::hash_list &merkle)
{
    // Stop if hash list is empty or contains one element
    if (merkle.empty())
        return bc::null_hash;
    else if (merkle.size() == 1)
        return merkle[0];
    // While there is more than 1 hash in the list, keep looping...
    while (merkle.size() > 1)
    {
        // If number of hashes is odd, duplicate last hash in the list.
        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());
        // List size is now even.
        assert(merkle.size() % 2 == 0);
        // New hash list.
        bc::hash_list new_merkle;
        // Loop through hashes 2 at a time.
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            // Join both current hashes together (concatenate).
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
                decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
            // Hash both of the hashes.
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
            // Add this to the new list.
            new_merkle.push_back(new_root);
        }
        // This is the new list.
        merkle = new_merkle;
        // DEBUG output -------------------------------------
       /*  std::cout << "Current merkle hash list:" << std::endl;
        for (const auto &hash : merkle)
            std::cout << " " << bc::encode_base16(hash) << std::endl;
        std::cout << std::endl; */
        // --------------------------------------------------
    }
    // Finally we end up with a single item.
    return merkle[0];
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