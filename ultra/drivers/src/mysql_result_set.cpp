#include "mysql_result_set.hpp"
#include <cppconn/metadata.h>
#include <iomanip>
namespace quick {
namespace ultra {
MySQLResultSet::MySQLResultSet(sql::ResultSet* rs)
    : result_set_(rs) {}

MySQLResultSet::~MySQLResultSet() = default;

bool MySQLResultSet::next() {
    return result_set_->next();
}

int MySQLResultSet::get_int(const std::string& column) {
    return result_set_->getInt(column);
}

std::string MySQLResultSet::get_string(const std::string& column) {
    return result_set_->getString(column).c_str(); 
}

bool MySQLResultSet::get_bool(const std::string& column) {
    return result_set_->getBoolean(column); 
}

double MySQLResultSet::get_double(const std::string& column) {
    return result_set_->getDouble(column); 
}
char MySQLResultSet::get_char(const std::string& column) {
    return result_set_->getString(column)[0]; 
}

std::string MySQLResultSet::debug() {
    if (!result_set_) {
        return "[empty result set]\n";
    }

    std::ostringstream oss;

    sql::ResultSetMetaData* meta = result_set_->getMetaData();
    int col_count = meta->getColumnCount();

    if (col_count == 0) {
        oss << "Result set: 0 columns\n--------\n(no rows)\n";
        return oss.str();
    }

    struct RowData {
        std::vector<std::string> cells;
    };

    std::vector<std::string> headers;
    std::vector<size_t> col_widths(col_count, 0);

    headers.reserve(col_count);
    for (int i = 1; i <= col_count; ++i) {
        std::string label = meta->getColumnLabel(i);
        headers.push_back(label);
        col_widths[i-1] = std::max(col_widths[i-1], label.length());
    }

    std::vector<RowData> rows;
    while (result_set_->next()) {
        RowData row;
        row.cells.reserve(col_count);
        for (int i = 1; i <= col_count; ++i) {
            std::string value;
            try {
                value = result_set_->getString(i);
                if (result_set_->wasNull()) {
                    value = "NULL";
                }
            } catch (const sql::SQLException& e) {
                value = "<ERR>";
            }
            row.cells.push_back(value);
            col_widths[i-1] = std::max(col_widths[i-1], value.length());
        }
        rows.push_back(std::move(row));
    }

    for (auto& w : col_widths) {
        w = std::max(w, size_t{3});
    }


    oss << '+';
    for (size_t w : col_widths) {
        oss << std::string(w + 2, '-') << '+';
    }
    oss << "\n";

    oss << '|';
    for (int i = 0; i < col_count; ++i) {
        oss << ' ' << std::left << std::setw(col_widths[i]) << headers[i] << " |";
    }
    oss << "\n";

    oss << '+';
    for (size_t w : col_widths) {
        oss << std::string(w + 2, '-') << '+';
    }
    oss << "\n";

    for (const auto& row : rows) {
        oss << '|';
        for (int i = 0; i < col_count; ++i) {
            oss << ' ' << std::left << std::setw(col_widths[i]) << row.cells[i] << " |";
        }
        oss << "\n";
    }

    if (!rows.empty()) {
        oss << '+';
        for (size_t w : col_widths) {
            oss << std::string(w + 2, '-') << '+';
        }
        oss << "\n";
    }

    oss << "(" << rows.size() << " row" << (rows.size() != 1 ? "s" : "") << ")\n";

    return oss.str();
}

Objects MySQLResultSet::to_vector_of_maps(){
    std::vector<std::unordered_map<std::string, std::string>> rows;

    if (!result_set_) {
        return rows;
    }

    sql::ResultSetMetaData* meta = result_set_->getMetaData();
    int col_count = meta->getColumnCount();

    while (result_set_->next()) {
        std::unordered_map<std::string, std::string> row;
        row.reserve(col_count);

        for (int i = 1; i <= col_count; ++i) {
            std::string col_name = meta->getColumnLabel(i);  
            try {
                std::string value = result_set_->getString(i);
                row[col_name] = value;
            } catch (const sql::SQLException& e) {
                row[col_name] = "<ERROR: " + std::string(e.what()) + ">";
            }
        }
        rows.push_back(std::move(row));
    }

    return rows;
}
}}// namespace quick::ultra
