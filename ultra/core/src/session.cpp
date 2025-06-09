#include "session.hpp"
#define DEBUG
namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver)
    : driver_(std::move(driver)) {

    switch (driver_->type()) {
        case DriverType::MySQL:
            dialect_ = std::make_unique<sqljke::MySQLDialect>();
            break;
        default:
            dialect_ = nullptr;
            break;
    }

    // create_tables();
}

void Session::create_tables(std::vector<sqljke::PureTable> tables) {
    auto builder = std::make_unique<sqljke::CreateTableQueryBuilder>(dialect_.get());

    builder->set_if_not_exists();
    for(auto& table : tables){
        builder->add_table(table.name_);
        for(auto column : table.columns_){
            builder->add_column(column);
        }
        auto links = table.links_;
        for(auto link : links){
            builder->add_foreign_key(link.column, link.foreign_table, link.foreign_column);
        }
    }

    auto queries = builder->build_all();
    for (const auto& sql : queries) {
#ifdef DEBUG
        std::cout << sql << std::endl;
#endif
        driver_->execute(sql);
    }
}

bool Session::is_exist(std::shared_ptr<sqljke::SQLTable> table) {
    auto query = std::make_unique<sqljke::SelectQueryBuilder>(dialect_.get());
    auto sql = query->select({}).from(table->table_name()).build();

#ifdef DEBUG
    std::cout << "Executing SQL: " << sql << std::endl;
#endif

    try {
        ResultSetPtr result = driver_->query(sql);

        if (!result) {
            std::cerr << "Query returned no result." << std::endl;
            return false;
        }

        bool has_rows = false;

        std::vector<std::string> column_names;
        for (const auto& col : table->columns()) {
            column_names.push_back(col.name);
        }

#ifdef DEBUG
        std::cout << "Columns: ";
        for (const auto& col : column_names) {
            std::cout << col << "\t";
        }
        std::cout << std::endl;
#endif

        while (result->next()) {
            has_rows = true;

#ifdef DEBUG
            std::cout << "Row:\n";
            for (const auto& col : column_names) {
                std::cout << "  " << col << ": " << result->get_string(col) << "\n";
            }
            std::cout << "--------\n";
#endif
        }

        return has_rows;

    } catch (const std::exception& e) {
        std::cerr << "Exception during query: " << e.what() << std::endl;
        return false;
    }
}


ResultSetPtr Session::select(sqljke::SelectQuery select_query){
    auto query = std::make_unique<sqljke::SelectQueryBuilder>(dialect_.get());
    auto sql = query->select(select_query.columns)
            .from(select_query.table_name)
            .where(select_query.where);

    try
    {
        sql.limit(std::get<int>(select_query.limit));
    }
    catch (const std::bad_variant_access& ex)
    {
        try
        {
            auto p = std::get<std::pair<int, int>>(select_query.limit);
            sql.limit(p.first, p.second);
        }
        catch(const std::bad_variant_access& ex)
        {
            std::cerr << "err " << ex.what() << std::endl; 
        }
    }
    std::cout << sql.build() << std::endl;

    try{
        auto result = driver_->query(sql.build());
    
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

void Session::insert_into(std::shared_ptr<sqljke::SQLTable> table) {
    auto query = std::make_unique<sqljke::InsertQueryBuilder>(dialect_.get());
    std::string sql = query->insert_into(table->table_name())
                              .columns(table->column_names())
                              .values(table->values())
                              .build();



#ifdef DEBUG
    std::cout << sql << std::endl;
#endif
    try{
        if(!is_exist(table)){
            driver_->execute(sql);
        }else{
            std::cout << "obj exist" << std::endl;
        }
    }catch(std::exception& ex){
        std::cout << ex.what() << std::endl;
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




}}// namespace quick::ultra
