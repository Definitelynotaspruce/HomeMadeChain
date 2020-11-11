#ifndef USER_H
#define USER_H

#include <string>

class User
{
    public:
    std::string name;
    std::string public_key;
    int balance;

    User();
    User(int);


};

#endif