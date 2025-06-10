#include "session.hpp"
namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver)
    : driver_(std::move(driver)),
      dialect_(),
      select_(dialect_.get()),       
      create_(dialect_.get()),      
      insert_(dialect_.get())       
{
    switch (driver_->type()) {
        case DriverType::MySQL:
            dialect_ = std::make_unique<sqljke::MySQLDialect>();
            break;
        default:
            dialect_ = nullptr;
            break;
    }

    select_ = sqljke::SelectQueryBuilder(dialect_.get());
    create_ = sqljke::CreateTableQueryBuilder(dialect_.get());
    insert_ = sqljke::InsertQueryBuilder(dialect_.get());
}

void Session::create_tables(std::vector<std::shared_ptr<sqljke::SQLTable>> tables) {

    create_.set_if_not_exists();
    for(auto& table : tables){
        create_table(table->table_name());
        for(auto column : table->columns()){
            create_.add_column(column);
        }
        auto links = table->links();
        for(auto link : links){
            create_.add_foreign_key(link.column, link.foreign_table, link.foreign_column);
        }
    }
    auto queries = create_.build_all();

    for (const auto& sql : queries) {
#ifdef DEBUG
        std::cout << sql << std::endl;
#endif
        driver_->execute(sql);
    }
}

bool Session::is_exist(std::shared_ptr<sqljke::SQLTable> table) {
    return true;
}


ResultSetPtr Session::execute(const std::string& sql){
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

void Session::save(std::shared_ptr<sqljke::SQLTable> table) {
    auto query = std::make_unique<sqljke::InsertQueryBuilder>(dialect_.get());
    std::string sql = insert_into(table->table_name())
                        .columns(table->column_names())
                        .values(table->values())
                        .build();


#ifdef DEBUG
    std::cout << sql << std::endl;
#endif
    try{
        driver_->execute(sql);
    }catch(std::exception& ex){
        std::cerr << ex.what() << std::endl;
    }
    
#ifdef DEBUG
    std::cout << sql << std::endl;
#endif
}

void Session::drop_table() {
    // auto query = std::make_unique<DropTableQueryBuilder>(dialect_.get());
    // std::string sql = builder->drop_table("users").if_exists().build();
    // driver_->execute(sql);
}

sqljke::SelectQueryBuilder& Session::select(const std::vector<std::string>& columns){
    select_.set_columns(columns);
    return select_;
}

sqljke::CreateTableQueryBuilder& Session::create_table(const std::string& table_name){
    create_.set_table_name(table_name);
    return create_;
}

sqljke::InsertQueryBuilder& Session::insert_into(const std::string& table_name){
    insert_.set_table(table_name);
    return insert_;
}

void Session::drop_database(const std::string& database_name){
    execute("drop database " + database_name + ";");
}


}}// namespace quick::ultra
