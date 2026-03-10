#include "session.hpp"
#include "column.hpp"
namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver)
    : driver_(std::move(driver)),
      dialect_(),
      select_(dialect_.get()),       
      create_(dialect_.get()),      
      insert_(dialect_.get()),
      update_(dialect_.get()),
      delete_(dialect_.get())   
{
    switch (driver_->type()) {
        case DRIVER_TYPE::MY_SQL:
            dialect_ = std::make_unique<sqljke::MySQLDialect>();
            break;
        default:
            dialect_ = nullptr;
            break;
    }

    select_ = sqljke::SelectQueryBuilder(dialect_.get());
    create_ = sqljke::CreateTableQueryBuilder(dialect_.get());
    insert_ = sqljke::InsertQueryBuilder(dialect_.get());
    update_ = sqljke::UpdateQueryBuilder(dialect_.get());
    delete_ = sqljke::DeleteQueryBuilder(dialect_.get());
}

Status Session::create_tables(std::vector<std::shared_ptr<sqljke::SQLTable>> tables) {

    create_.set_if_not_exists();
    for(auto& table : tables){
        create_table(table->table_name());
        for(auto column : table->columns()){
            create_.add_column(column);
        }
        for(auto link : table->links()){
            create_.add_foreign_key(link);
        }
    }
    auto queries = create_.build();

    for (const auto& sql : queries) {
        driver_->execute(sql);
    }

    return OK;
}

ResultSetPtr Session::execute(const std::string& sql) {
    try{
        auto result = driver_->query(sql);
        if (!result) {
            std::cerr << "Query returned no result." << std::endl;
            return ResultSetPtr();
        }else{
            return result;
        }
    }catch (const std::exception& e) {
        std::cerr << "Exception during query: " << e.what() << std::endl;
        return ResultSetPtr();
    }
}

sqljke::SelectQueryBuilder& Session::select(const std::vector<std::variant<sqljke::Column, sqljke::Aggregate, sqljke::Scalar>> select_list) {
    select_.reset();  
    select_.set_select_list(select_list);
    return select_;
}

sqljke::CreateTableQueryBuilder& Session::create_table(const std::string& table_name) {
    create_.set_table_name(table_name);
    return create_;
}

sqljke::InsertQueryBuilder& Session::insert_into(const std::string& table_name) {
    insert_.set_table(table_name);
    return insert_;
}

sqljke::UpdateQueryBuilder& Session::update(const sqljke::Table& table_name) {
    update_.reset();  
    update_.set_table(table_name);
    return update_;
}

sqljke::DeleteQueryBuilder& Session::delete_from(const sqljke::Table& table) {
    delete_.set_table(table);
    return delete_;
}


}} // namespace quick::ultra
