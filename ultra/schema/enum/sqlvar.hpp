#ifndef SCHEMA_SQL_VAR_H
#define SCHEMA_SQL_VAR_H
#include <string>

enum SQLVAR{
    INT,
    STRING,
    OBJECT,
    VECTOR

};

inline std::string varToString(SQLVAR type) {
    switch (type) {
        case SQLVAR::INT:     return "INT";
        case SQLVAR::STRING:  return "VARCHAR(255)";
        case SQLVAR::OBJECT:  return "OBJECT";
        case SQLVAR::VECTOR:  return "VECTOR";
        default:              return "UNKNOWN";
    }
}


inline SQLVAR stringToSQLVAR(const std::string& str) {
    if (str == "int") return SQLVAR::INT;
    else if (str == "std::string") return SQLVAR::STRING;
    else if (str.find("std::vector<") != std::string::npos) return SQLVAR::VECTOR;
    else return SQLVAR::OBJECT; 
}

#endif