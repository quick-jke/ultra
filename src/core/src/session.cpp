#include "session.hpp"
#define DEBUG
namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver)
    : driver_(std::move(driver)) {

    switch (driver_->type()) {
        case DriverType::MySQL:
            dialect_ = std::make_unique<MySQLDialect>();
            break;
        default:
            dialect_ = nullptr;
            break;
    }

    create_tables();
}

void Session::create_tables(/* std::span<SQLTable> tables */) {
    auto builder = std::make_unique<CreateTableQueryBuilder>(dialect_.get());

    /*

    //need to sort std::span
    builder->set_if_not_exists();
    for(auto table : tables){
        builder.add_table(table.table_name());
        for(auto column : table.columns()){
            builder.add_column(column);
        }
        auto links = table.links();
        for(auto link : links){
            builder.add_goreign_key(link.to_foreign_key);
        }
    }

    */

    builder->set_if_not_exists()
           .add_table("users")
           .add_column(Column{"id", "INT", true, true, false, ""})
           .add_column(Column{"name", "VARCHAR(255)", false, false, true, "'default'"})
           .add_column(Column{"age", "INT", false, false, false, "0"});

    builder->add_table("orders")
           .add_column(Column{"order_id", "INT", true, true, false, ""})
           .add_column(Column{"user_id", "INT", false, false, false, ""})
           .add_column(Column{"total", "DECIMAL(10,2)", false, false, false, ""})
           .add_foreign_key("user_id", "users", "id");

    auto queries = builder->build_all();
    for (const auto& sql : queries) {
#ifdef DEBUG
        std::cout << sql << std::endl;
#endif
        driver_->execute(sql);
    }
}


//temp method

/*

struct SelectQuery{
    std::vector<std::string> what;
    Table from;
    std::string where;
    std::variant<std::string, int> limit;
};

SelectQuery squery = {
    {table.id, table.name, table.age},
    table.table_name(),
    table.ageMoreThan(30),
    10
};

*/
ResultSetPtr Session::select(/* SelectQuery squery */){
    auto query = std::make_unique<SelectQueryBuilder>(dialect_.get());

    /*
    auto sql = query->select(squery.what)
            .from(squery.from.table_name())
            .where(squery.where)
            .limit(squery.limit)
            .build();
    */

    auto sql = query->select({"id", "name", "age"})
            .from("users")
            .where("age > 30")
            .limit(2, 2)
            .build();

    std::cout << sql << std::endl;

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

//furure
void Session::insert_into(/* SQLTable table */) {

    /*
    
    auto query = std::make_unique<InsertQueryBuilder>(dialect_.get());

    std::string sql = query->insert_into(table.table_name())
                              .columns(table.columns())
                              .values(table.values())
                              .build();
    std::cout << sql << std::endl;
    driver_->execute(sql);
    
    */

    auto query = std::make_unique<InsertQueryBuilder>(dialect_.get());

    std::string sql = query->insert_into("users")
                              .columns({"name", "age"})
                              .values({"Alice", "35"})
                              .build();
    std::cout << sql << std::endl;
    driver_->execute(sql);
}

void Session::drop_table() {
    // auto query = std::make_unique<DropTableQueryBuilder>(dialect_.get());
    // std::string sql = builder->drop_table("users").if_exists().build();
    // driver_->execute(sql);
}




}}// namespace quick::ultra