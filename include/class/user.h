#ifndef USER_H
#define USER_H

#include <string>

class user
{
    public:
    std::string name;
    std::string public_key;
    int balance;

    user();
    user(int);


};

#endif