//#include "include/functions.h"
#include "include/class/user.h"
#include "include/class/transaction.h"
#include "include/class/block.h"
#include "include/class/chain.h"
#include "include/headers/hash.h"

#include <iostream>
#include <random>
#include <ctime>

#define userNum 10
#define transactionNum 100
#define transactionInBlockNum 10

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
        transactions.push_back(Transaction(users[rand() % userNum], users[rand() % userNum]));
        //printDetailedTransactionInfo(transactions[i]);
    }
    std::cout << "Generation of transactions was done successfully!!\n";

    return transactions;
}

std::vector<Transaction *> pickRandomTransactions(std::vector<Transaction> &transactionPool, int num)
{
    std::cout << "Picking " << num << " random Transactions...\n";
    srand(std::time(0));
    std::vector<Transaction *> transInBlock;
    for (int i = 0; i < num; i++)
    {
        transInBlock.push_back(&(transactionPool[rand() % transactionInBlockNum]));
        //printDetailedTransactionInfo(*transInBlock[i]);
    }
    std::cout << "Picking of random Transactions was done successfully!\n";

    return transInBlock;
}

void validateTransactions(std::vector<Transaction *> &transInBlock)
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
            std::cerr << msg << std::endl;
            transInBlock.erase(it--);
        }
    }
    std::cout << "Validation of picked Transactions completed!\n";
}

void removeTransFromPool(std::vector<Transaction *> &transInBlock)
{
    std::cout << "Removal of picked Transactions from transactionPool started...\n";
    for (auto it = transInBlock.begin(); it != transInBlock.end(); it++)
    {        
        transInBlock.erase(it--);
    }
    std::cout << "Removal of picked Transactions from transactionPool completed!\n";
}

int main()
{
    Chain *head = new Chain(Block());
    Chain *tail = head;

    std::string prevBlock = hash(blockToString(head->currentBlock));

    std::vector<User> users = generateUsers(userNum);
    std::vector<Transaction> transactionPool = generateTransactions(transactionNum, users);

    while (!transactionPool.empty())
    {
        std::vector<Transaction *> TransInBlock = pickRandomTransactions(transactionPool, transactionInBlockNum);
        validateTransactions(TransInBlock);
        head->addToChain(Block(TransInBlock, prevBlock));
        removeTransFromPool(TransInBlock);
        std::cout << "Size of transactionPool after removal: " << transactionPool.size();
    }

    std::cout << "I think its done " << transactionPool.size() << std::endl;

    return 0;
}