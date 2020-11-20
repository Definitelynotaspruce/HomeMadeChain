# HomeMadeChain
Homemade blockchain for uni project

## Main idea

*HomeMadaChain* is a **extra** simplified version of bitcoin blockchain.

## Structure of *HomeMadeChain* program

+ class *User*
+ class *Transaction*
+ class *Block* (header + transactions)
+ hash from [**NeonRice**](https://github.com/NeonRice/Rice_Hash)
+ a lot of tears

## How does *HomeMadeChain* even work?
1. *Users* with random balances are generated and stored into *std::vector*
2. *TransactionPool* is generated and stored into *std::vector*
3. Mining till *transactionPool* is empty
```c++
 while(!transactionPool.empty())
    mineTheBlock();
 ```
4. Validation and verification are done before mining the block.
5. After finding the right **nonce** transactions are executed and balances of *Users* are updated.
6. Blocks are stored in a *linkedlist*

## NEW IN [**v0.2**](https://github.com/Definitelynotaspruce/HomeMadeChain/releases/tag/0.2) !!!

### *MerkleRoot* finder 
```c++
std::string Block::merkleRoot()
{
    std::vector<std::string> temp = transactionIDs;
    std::vector<std::string> temp2;
    while (temp.size() > 1)    {
        if (temp.size() & 1) 
            temp.push_back(temp.back());
        for (int i = 0; i < temp.size(); i += 2)    
            temp2.push_back(hash(temp[i] + temp[i + 1])); 
        temp = temp2;
        temp2.clear();
    }
    return temp[0];
}
```

## Some code snippets from my beloved *HomeMadeChain* 

Checking if transaction is valid:
```c++
void validateTransactions(std::vector<Transaction*> &tInBlock, std::vector<Transaction> &tPool)
{
    for (auto it = tInBlock.begin(); it != tInBlock.end(); it++)
    {
        try{
            validateTransaction(**it); }
        catch (const char *msg) {
            tPool.erase(std::remove(transactionPool.begin(), tPool.end(), **it), tPool.end());
            tInBlock.erase(it--);
        }
    }
}
```
Mining is done in *Block* class constructor 
```c++
    std::string str = hash(blockToString(*this));
    std::string str2(difficulty_target, '0');
    unsigned long long count = 0; // limit attempts to find the right nonce

    while (str.substr(0, difficulty_target) != str2) 
    {
        nonce = rand();
        str = hash(blockToString(*this));
        if (count++ > 1000) 
            throw "\nOh no you need to stop";
    }
```

## Want to run this program by yourself?  
1. Download the release
2. Compile the program:
<br>*g++ block.cpp main.cpp user.cpp transaction.cpp .\include\headers\hash.cpp*
3. Run the *exe* or binary file
4. Enjoy

# My final words
+ Sadly I failed to use *multithreading* technology to mine blocks
+ *undefined behavior* follows me everywhere
+ Special thanks to [NeonRice](https://github.com/NeonRice) for his patience and love for 🍙

 ## <i>Releases</i>
 
[**[v0.2]**](https://github.com/Definitelynotaspruce/HomeMadeChain/releases/tag/0.2) - added function to find *MerkleRoot* 

