#include "include/functions.h"

bool stopThread = false;

const std::vector<User> generateUsers(int num)
{
    std::cout << "Generating " << num << " new users...\n";
    std::vector<User> users;
    users.reserve(num);
    for (int i = 0; i < num; i++)
    {
        users.push_back(User(i));
    }
    std::cout << "Generation of users was done successfully!!\n";

    return users;
}

std::vector<Transaction> generateTransactions(int num, std::vector<User> &users)
{
    std::cout << "Generating " << num << " new transactions...\n";
    std::vector<Transaction> transactions;
    transactions.reserve(num);

    for (int i = 0; i < num; i++)
    {
        User *u1 = &users[rand() % userNum];
        User *u2 = &users[rand() % userNum];
        if (u1->public_key != u2->public_key)
            transactions.push_back(Transaction(*u1, *u2));
    }
    std::cout << "Generated " << transactions.size() << " transactions, completed!!\n";

    return transactions;
}

std::vector<Transaction *> pickRandomTransactions(std::vector<Transaction> &transactionPool, int num)
{

    std::cout << "Trying to pick " << num << " transactions from transactionPool...\n";
    srand(std::time(0));
    std::vector<Transaction *> transInBlock;

    if (num > transactionPool.size())
    {
        num = transactionPool.size();
        for (int i = 0; i < num; i++)
        {
            auto trans = &(transactionPool[rand() % num]);
            try
            {
                validateTransaction(*trans);
                transInBlock.push_back(trans);
            }
            catch (const char *msg)
            {
                std::cout << msg << std::endl;
            }
        }
    }

    else
    {
        for (int i = 0; i < num; i++)
        {
            auto trans = &(transactionPool[rand() % num]);
            try
            {
                validateTransaction(*trans);
                transInBlock.push_back(trans);
            }
            catch (const char *msg)
            {
                std::cout << msg << std::endl;
            }
        }
    }
    std::cout << "Picked " << transInBlock.size() << " transactions, completed!\n";

    return transInBlock;
}

void validateTransactions(std::vector<Transaction *> &transInBlock, std::vector<Transaction> &transactionPool)
{
    std::cout << "Validation of picked Transactions started...\n";
    for (auto it = transInBlock.begin(); it != transInBlock.end(); it++)
    {
        try
        {
            validateTransaction(**it);
        }
        catch (const char *msg)
        {
            transactionPool.erase(std::remove(transactionPool.begin(), transactionPool.end(), **it), transactionPool.end());
            transInBlock.erase(it--);
        }
    }
    std::cout << "Validated " << transInBlock.size() << " transactions, completed!!\n";
}

void execRemoveTransFromPool(std::vector<Transaction *> &transInBlock, std::vector<Transaction> &transactionPool)
{
    std::cout << "Removal of " << transInBlock.size() << " picked Transactions from transactionPool started...\n";
    for (auto it = transInBlock.begin(); it != transInBlock.end(); it++)
    {
        try
        {
            if (!((**it).sender->balance = (**it).sender->balance - (**it).sum))
            {
                throw "sender balance not enough";
            }
            (**it).receiver->balance = (**it).receiver->balance + (**it).sum;
            transactionPool.erase(std::remove(transactionPool.begin(), transactionPool.end(), **it), transactionPool.end());
            transInBlock.erase(it--);
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
    }
    std::cout << "Removed transactions from the transactionPool, completed!\n";
}

void mineTheBlock(std::vector<Transaction> &transactionPool, std::string &prevBlock, Block *last, unsigned tryNum)
{
    std::vector<Transaction *> transInBlock = pickRandomTransactions(transactionPool, transactionInBlockNum);
    if (transInBlock.empty())
        return;
    try
    {
        Block *current = new Block(transInBlock, prevBlock);
        last->prev = current;
        validateTransactions(transInBlock, transactionPool);
        execRemoveTransFromPool(transInBlock, transactionPool);
        prevBlock = hash(blockToString(*current));
        last = current;
        std::cout << "Size of transactionPool after removal: " << transactionPool.size() << std::endl;
        std::cout << std::endl;
        transInBlock.clear();
    }
    catch (const char *msg)
    {
        std::cout << msg << std::endl;
        transInBlock.clear();
        return;
    }
}

int main()
{
    Block *first = new Block();
    Block *last = first;
    unsigned tryNum = 1000;

    std::string prevBlock = hash(blockToString(*last));

    std::vector<User> users = generateUsers(userNum);
    std::vector<Transaction> transactionPool = generateTransactions(transactionNum, users);

    while (!transactionPool.empty())
    {
        for (int i = 0; i < 5; i++)
        {
            mineTheBlock(transactionPool, prevBlock, last, tryNum);
            if (transactionPool.empty())
                break;
        }
    }

    std::cout << "Transaction pool is empty " << transactionPool.size() << std::endl;

    return 0;
}