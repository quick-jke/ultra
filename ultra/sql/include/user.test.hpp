

#include <string>
#include <vector>
#include "column.hpp"
struct SQLTable{

};

namespace hello{

struct Link{
    const std::string& column;
    const std::string& foreign_table;
    const std::string& foreign_column;

};


class User : public SQLTable{
public:
    User(){

    }

    std::string name(){
        return name_;
    }

    void set_name(const std::string& name){
        name_ = name;
    }

    int age(){
        return age_;
    }

    void set_age(int age){
        age_ = age;
    }

    

    //sql
    std::string table_name(){
        return "users";
    }

    std::vector<quick::ultra::Column> columns(){
        return {
            {"id", "INT", true, true, false, ""},
            {"name", "VARCHAR(255)", false, false, true, "'default'"},
            {"age", "INT", false, false, false, "0"}
        };
    }

    std::vector<Link> links(){
        return {};
    }

    std::vector<std::string> values(){
        return {std::to_string(id_), name_, std::to_string(age_)};
    }

    std::string ageMoreThan(int value){
        return "age > " + std::to_string(value);
    }

private:
    int id_;
    std::string name_;
    int age_;
};

}