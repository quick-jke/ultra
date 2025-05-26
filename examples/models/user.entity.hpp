#ifndef USER_ENTITY
#define USER_ENTITY

#include <string>
#include "macros.hpp"

IMPORT Product;
IMPORT Passport;
IMPORT SomeProduct;


ENTITY User {
    
    ID int id;

    std::string name;

    std::string email;

    ONE_TO_MANY(Product) products;

    ONE_TO_ONE(Passport) pass;

    MANY_TO_MANY(SomeProduct) some_products;

};

#endif