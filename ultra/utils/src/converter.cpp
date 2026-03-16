#include "converter.hpp"

std::string variant_to_string(std::variant<std::string, int, double, bool> const & value) {
    if (auto const* pval = std::get_if<int>(&value)) {
        return std::to_string(*pval);
    }

    if (auto const* pval = std::get_if<double>(&value)) {
        return std::to_string(*pval);
    }

    if (auto const* pval = std::get_if<bool>(&value)) {
        return *pval ? "1" : "0"; 
    }

    return std::get<std::string>(value);
}
