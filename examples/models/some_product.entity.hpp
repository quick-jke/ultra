#ifndef SOME_PRODUCT
#define SOME_PRODUCT

#include "macros.hpp"
#include <string>

IMPORT User;

ENTITY SomeProduct{
    
    ID int id;

    MANY_TO_MANY(User) users;

    std::string text;
};

#endif