//#include "include/functions.h"
#include "include/class/user.h"
#include "include/class/transaction.h"
#include <iostream>
#include <random>
#include "include/headers/hash.h"

#define userNum 100
#define transactionNum 10000

std::vector<user> generateUsers(int num)
{   
    std::vector<user> users;
    for (int i = 0; i < num; i++)
    {
        users.push_back(user(i));
    } 
    return users;
}

std::vector<transaction> generateTransactions(int num, std::vector<user> users)
{   
    std::vector<transaction> transactions;

    for (int i = 0; i < num; i++)
    {
        transactions.push_back(transaction(users[rand() % userNum + 1 ].public_key, users[rand() % userNum + 1].public_key));
        std::cout << transactions[i].ID << std::endl; 
    } 
    return transactions;
}

int main()
{
    std::vector<user> users = generateUsers(userNum);
    std::vector<transaction> transactionPool = generateTransactions(transactionNum, users); 
    return 0;
}