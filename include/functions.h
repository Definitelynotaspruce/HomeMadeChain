#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "class/user.h"
#include "class/transaction.h"

std::vector<user> generateUsers(int);
std::vector<transaction> generateTransactions(int, std::vector<user>);

#endif