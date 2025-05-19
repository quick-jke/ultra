#ifndef PRODUCT
#define PRODUCT

#include "macros.hpp"
#include "user.entity.hpp"
#include <string>

ENTITY
struct Product{
    ID
    int id;

    std::string info;

    MANY_TO_ONE
    User user;
};


#endif