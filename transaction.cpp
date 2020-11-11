#include "include/class/transaction.h"

//constructor with random sum
Transaction::Transaction(User &sender, User &reciever)
{
    this->sender = &sender;
    this->reciever = &reciever;
    sum = rand() % 1000 + 1;
    ID = hash(sender.public_key + reciever.public_key + std::to_string(sum));
}

// constructor with set sum
Transaction::Transaction(User &sender, User &reciever, int money)
{
    this->sender = &sender;
    this->reciever = &reciever;
    sum = money;
    ID = hash(this->sender->public_key + this->reciever->public_key + std::to_string(sum));
}

bool validateTransaction(Transaction &transaction)
{
    // check if user exists
    if (transaction.sender->public_key.empty() || transaction.reciever->public_key.empty())
        throw "User does not exist!";
    else if (transaction.sender->public_key == transaction.reciever->public_key)
        throw "Sender and reciever are the same";
    //check balance of the sender
    else if ((transaction.sender->balance - transaction.sum) <= 0)
        throw "Sender balance is not enough";

    return true;
}

std::string getTransactionInfo(Transaction transaction)
{
    return ("senderPK:   " + transaction.sender->public_key + "\nrecieverPK: " + transaction.reciever->public_key + "\nsum: " + std::to_string(transaction.sum) + "\n");
}

void printDetailedTransactionInfo(Transaction transaction)
{
    std::cout << "Transaction between " << transaction.sender->name
              << " and " << transaction.reciever->name << std::endl;
    std::cout << getTransactionInfo(transaction) << std::endl;
}

std::string transToString(Transaction transaction)
{
    std::stringstream ss;
    ss << transaction.ID << transaction.sender->name 
    << transaction.reciever->name << transaction.sum;
     
    return ss.str();
}