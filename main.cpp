//#include "include/functions.h"
#include "include/class/user.h"
#include "include/class/transaction.h"
#include <iostream>
#include <random>
#include "include/headers/hash.h"

#define userNum 10
#define transactionNum 100

std::vector<User> generateUsers(int num)
{   
    std::vector<User> users;
    users.reserve(num);
    for (int i = 0; i < num; i++)
    {
        users.push_back(User(i));
        std::cout << getUserInfo(users[i]) << std::endl;
    } 
    return users;
}

std::vector<Transaction> generateTransactions(int num, std::vector<User> users)
{   
    std::vector<Transaction> transactions;
    transactions.reserve(num);

    for (int i = 0; i < num; i++)
    {
        transactions.push_back(Transaction(users[rand() % userNum], users[rand() % userNum]));
        std::cout << "Transaction nr: " << i << ", between " << transactions[i].sender->name 
        << " and " << transactions[i].reciever->name << std::endl;
        std::cout << getTransactionInfo(transactions[i]) << std::endl;

        try {
            std::cout << validateTransaction(transactions[i]) << std::endl;
        } catch (const char* msg) {
            std::cerr << msg << std::endl;
        }         
    } 

    std::cout << "size of vector " << transactions.size() << std::endl;
    return transactions;
}

int main()
{
    std::vector<User> users = generateUsers(userNum);
    std::vector<Transaction> transactionPool = generateTransactions(transactionNum, users); 

    // take 100 transacitons? (10 for me now)
    
    // validate them???
    // mine the block
    return 0;
}