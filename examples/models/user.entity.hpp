#ifndef USER_ENTITY
#define USER_ENTITY
#include "macros.hpp"
#include <string>
#include <vector> 
#include "passport.entity.hpp"


class Product;
class SomeProduct;

ENTITY
struct User {
    ID
    int id;

    std::string name;

    int age;

    ONE_TO_MANY
    std::vector<Product*> products;

    ONE_TO_ONE
    Passport pass;

    MANY_TO_MANY
    std::vector<SomeProduct*> some_products;

};

#endif