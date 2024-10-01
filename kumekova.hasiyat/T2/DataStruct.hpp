#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>

namespace kumekova
{
    struct DataEntry
    {
        unsigned long long primaryKey;
        unsigned long long secondaryKey;
        std::string thirdKey;
        bool operator<(const DataEntry& value) const;
    };

    std::istream& operator>>(std::istream& in, DataEntry& value);
    std::ostream& operator<<(std::ostream& out, const DataEntry& value);
}

#endif
