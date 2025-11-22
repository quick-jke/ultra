#ifndef QUICK_ULTRA_SQL_ENUM_ORDER_DIR_HPP
#define QUICK_ULTRA_SQL_ENUM_ORDER_DIR_HPP
namespace quick::ultra::sqljke {
enum class ORDER_DIR{
    ASC,
    DESC
};

inline std::string order_dir_to_string(ORDER_DIR od){
    switch (od){
        case ORDER_DIR::ASC:   return "ASC";
        case ORDER_DIR::DESC:  return "DESC";
        default:    return "UNKNOWN";
    }
}
}
#endif
