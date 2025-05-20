#ifndef PRODUCT
#define PRODUCT

#include "macros.hpp"
#include <string>

IMPORT User;

ENTITY Product{
    
    ID int id;

    std::string info;

    MANY_TO_ONE(User) user;
};


#endif