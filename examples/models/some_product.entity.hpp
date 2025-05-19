#ifndef SOME_PRODUCT
#define SOME_PRODUCT

#include "macros.hpp"
#include "user.entity.hpp"
#include <string>

ENTITY
struct SomeProduct{
    ID
    int id;

    MANY_TO_MANY
    std::vector<User> users;

    std::string text;
};

#endif