#ifndef QUICK_ULTRA_SCHEMA_DEP_HPP
#define QUICK_ULTRA_SCHEMA_DEP_HPP


#include "option.hpp"
#include <set>
#include <utility>
#include <algorithm>
#include <string>
#include <map>

namespace quick{
namespace ultra{

using tables = std::pair<std::string, std::string>;
using dependency = std::pair<OPTION, tables>;
using dependenciesByTables = std::map<std::string, std::set<std::string>>;

struct DependencyComparator {
    bool operator()(const dependency& lhs, const dependency& rhs) const {
        OPTION lhsOption = lhs.first;
        OPTION rhsOption = rhs.first;

        std::string lhsFrom = lhs.second.first;
        std::string lhsTo = lhs.second.second;

        std::string rhsFrom = rhs.second.first;
        std::string rhsTo = rhs.second.second;

        if (lhsOption == MANY_TO_MANY && rhsOption == MANY_TO_MANY) {
            auto keyLhs = std::minmax({ lhsFrom, lhsTo });
            auto keyRhs = std::minmax({ rhsFrom, rhsTo });
            return keyLhs < keyRhs;
        }

        auto normLhs = lhsOption == ONE_TO_MANY
            ? std::make_pair(lhsFrom, lhsTo)
            : lhsOption == MANY_TO_ONE
            ? std::make_pair(lhsTo, lhsFrom)
            : std::make_pair(lhsFrom, lhsTo);

        auto normRhs = rhsOption == ONE_TO_MANY
            ? std::make_pair(rhsFrom, rhsTo)
            : rhsOption == MANY_TO_ONE
            ? std::make_pair(rhsTo, rhsFrom)
            : std::make_pair(rhsFrom, rhsTo);

        OPTION normLhsOption = lhsOption == MANY_TO_ONE ? ONE_TO_MANY : lhsOption;
        OPTION normRhsOption = rhsOption == MANY_TO_ONE ? ONE_TO_MANY : rhsOption;

        if (normLhsOption != normRhsOption) {
            return normLhsOption < normRhsOption;
        }

        if (normLhs.first != normRhs.first) {
            return normLhs.first < normRhs.first;
        }

        return normLhs.second < normRhs.second;
    }
};

using dependencies = std::set<dependency, DependencyComparator>;
using dependenciesByTables = std::map<std::string, std::set<std::string>>;

using field = std::string;
using table_struct = std::pair<std::string, std::set<field>>;

}}

#endif