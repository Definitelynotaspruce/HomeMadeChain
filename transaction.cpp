#include "include/class/transaction.h"

/* Transaction::Transaction() 
{
    ID = "";
    sender_public_key = "sender";
    reciever_public_key = "reciever_public_key";
} */

//constructor with random sum
Transaction::Transaction(User& sender, User& reciever) 
{ 
    this->sender = &sender;
    this->reciever = &reciever;
    sum = rand() % 1000 + 1;
    ID = hash(sender.public_key + reciever.public_key + std::to_string(sum));
}

// constructor with set sum
Transaction::Transaction(User& sender, User& reciever, int money) 
{ 
    this->sender = &sender;
    this->reciever = &reciever;
    sum = money;
    ID = hash(this->sender->public_key + this->reciever->public_key + std::to_string(sum));
}

bool validateTransaction(Transaction transaction)
{
    // check if user exists
    if (transaction.sender->public_key.empty() || transaction.reciever->public_key.empty())
        throw "User does not exist!";
    //check balance of the sender
    else if ( (transaction.sender->balance - transaction.sum) <= 0 )
        throw "Sender balance is not enough";
    
    return true;
}  

std::string getTransactionInfo( Transaction transaction)
{
    return ("senderPK:   " + transaction.sender->public_key + "\nrecieverPK: " + transaction.reciever->public_key + "\nsum: " + std::to_string(transaction.sum) + "\n");
}