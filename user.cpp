#include "include/class/user.h"
#include "include/headers/hash.h"
#include <random>

User::User() 
{
    name = "user"; 
    public_key = "public_key"; 
    balance  = 100; 
}

User::User(int num) 
{ 
    name = "user" + std::to_string(num); 
    public_key = hash(name); 
    balance = rand() % 10000 + 1; 
}