#include "include/class/transaction.h"

//constructor with random sum
Transaction::Transaction(User &sender, User &receiver)
{
    this->sender = &sender;
    this->receiver = &receiver;
    sender_public_key = sender.public_key;
    receiver_public_key = receiver.public_key;
    sum = rand() % 1000 + 1;
    ID = hash(sender.public_key + receiver.public_key + std::to_string(sum));
}

// constructor with set sum
Transaction::Transaction(User &sender, User &receiver, int money)
{
    this->sender = &sender;
    this->receiver = &receiver;
    sender_public_key = sender.public_key;
    receiver_public_key = receiver.public_key;
    sum = money;
    ID = hash(this->sender->public_key + this->receiver->public_key + std::to_string(sum));
}

bool Transaction::operator==(const Transaction &other) const // copy assignment
{
    if (this->ID == other.ID)
        return true;
    return false;
}

bool validateTransaction(Transaction &transaction)
{
    // check if user exists
    if (transaction.sender->public_key.empty() || transaction.receiver->public_key.empty())
        throw "User does not exist!";
    else if (transaction.sender->public_key == transaction.receiver->public_key)
        throw "Sender and receiver are the same";
    //check balance of the sender
    else if ((transaction.sender->balance - transaction.sum) < 0)
        throw "Sender balance is not enough";
    else
    {
        std::string hash1 = hash(transaction.sender->public_key + transaction.receiver->public_key + std::to_string(transaction.sum));
        if (hash1 != transaction.ID)
            throw "OH NO SOMEONE MODIFIED THE TRANSACTION";
    }

    return true;
}

std::string getTransactionInfo(Transaction transaction)
{
    return ("senderPK:   " + transaction.sender->public_key + "\nreceiverPK: " + transaction.receiver->public_key + "\nsum: " + std::to_string(transaction.sum) + "\n");
}

void printDetailedTransactionInfo(Transaction transaction)
{
    std::cout << "Transaction between " << transaction.sender->name
              << " and " << transaction.receiver->name << std::endl;
    std::cout << getTransactionInfo(transaction) << std::endl;
}

std::string transToString(Transaction transaction)
{
    std::stringstream ss;
    ss << transaction.ID << transaction.sender->name
       << transaction.receiver->name << transaction.sum;

    return ss.str();
}