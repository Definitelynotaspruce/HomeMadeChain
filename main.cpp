//#include "include/functions.h"
#include "include/class/user.h"
#include "include/class/transaction.h"
#include "include/headers/hash.h"

#include <iostream>
#include <random>
#include <ctime>

#define userNum 10
#define transactionNum 100
#define transactionInBlockNum 100

const std::vector<User> generateUsers(int num)
{
    std::vector<User> users;
    users.reserve(num);
    for (int i = 0; i < num; i++)
    {
        users.push_back(User(i));
        //std::cout << getUserInfo(users[i]) << std::endl;
    }
    return users;
}

std::vector<Transaction> generateTransactions(int num, std::vector<User> &users)
{
    std::vector<Transaction> transactions;
    transactions.reserve(num);

    for (int i = 0; i < num; i++)
    {
        transactions.push_back(Transaction(users[rand() % userNum], users[rand() % userNum]));

        //info about transaction
        std::cout << "Transaction nr: " << i << ", between " << transactions[i].sender->name
                  << " and " << transactions[i].reciever->name << std::endl;
        std::cout << getTransactionInfo(transactions[i]) << std::endl;

        auto temp = transactions[i].sender->name;
        std::cout << "DEBUG " << temp << std::endl;

    }
    return transactions;
}

std::vector<Transaction *> pickRandomTransactions(std::vector<Transaction> &transactionPool, int num)
{
    srand(std::time(0));
    std::vector<Transaction *> transInBlock;
    for (int i = 0; i < num; i++)
    {
        transInBlock.push_back(&(transactionPool[rand() % transactionInBlockNum]));
        std::cout << "nr " << i << " " << transInBlock[i]->sender->name << std::endl;

        std::cout << i << " " << transactionPool[rand() % transactionInBlockNum].sender->name << std::endl;

        std::cout << "Transaction nr: " << i << ", between " << transInBlock[i]->sender->name
                  << " and " << transInBlock[i]->reciever->name << std::endl;
        std::cout << getTransactionInfo(*(transInBlock[i])) << std::endl;
    }

    return transInBlock;
}

void validateTransactions(std::vector<Transaction *> &transInBlock)
{
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
}

int main()
{
    std::vector<User> users = generateUsers(userNum);
    std::vector<Transaction> transactionPool = generateTransactions(transactionNum, users);
    // take 100 transacitons? (10 for me now)
    std::vector<Transaction *> TransInBlock = pickRandomTransactions(transactionPool, transactionInBlockNum);

    validateTransactions(TransInBlock);

    //std::cout << transactionPool[0].sender->name << std::endl;
    /* try {
            validateTransaction(TransInBlock[0]);
        } catch (const char* msg) {
            std::cerr << msg << std::endl;
        }   */

    // validate them???
    // mine the block
    return 0;
}