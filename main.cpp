//#include "include/functions.h"
#include "include/class/user.h"
#include "include/class/transaction.h"
#include <iostream>
#include <random>
#include "include/headers/hash.h"

#define userNum 100
#define transactionNum 10000

std::vector<User> generateUsers(int num)
{   
    std::vector<User> users;
    for (int i = 0; i < num; i++)
    {
        users.push_back(User(i));
    } 
    return users;
}

std::vector<Transaction> generateTransactions(int num, std::vector<User> users)
{   
    std::vector<Transaction> transactions;

    for (int i = 0; i < num; i++)
    {
        transactions.push_back(Transaction(users[rand() % userNum + 1 ].public_key, users[rand() % userNum + 1].public_key));
        std::cout << transactions[i].ID << std::endl; 
    } 
    return transactions;
}

int main()
{
    std::vector<User> users = generateUsers(userNum);
    std::vector<Transaction> transactionPool = generateTransactions(transactionNum, users); 
    return 0;
}