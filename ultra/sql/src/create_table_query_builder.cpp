#include "create_table_query_builder.hpp"
#include <iostream>

namespace quick::ultra::sqljke{

void CreateTableQueryBuilder::set_table_name(const std::string& table_name){
    ir_->tables.push_back({table_name, {}, {}});
}

CreateTableQueryBuilder& CreateTableQueryBuilder::set_if_not_exists(bool enable) {
    ir_->if_not_exists_ = enable;
    return *this;
}

CreateTableQueryBuilder& CreateTableQueryBuilder::add_column(const Column& column) {
    if (!ir_->tables.empty() ) {
        ir_->tables.back().columns.push_back(column);
    }
    return *this;
}

CreateTableQueryBuilder& CreateTableQueryBuilder::add_foreign_key(Link link) {
    if (!ir_->tables.empty()) {
        ir_->tables.back().foreign_keys.emplace_back(link);
    }
    return *this;
}

std::vector<std::string> CreateTableQueryBuilder::build() const {

    auto queries = dialect_->compile_create_table(*ir_);

    for(auto sql : queries) {
        std::cout << sql << std::endl;
    }

    return queries;
}

}
