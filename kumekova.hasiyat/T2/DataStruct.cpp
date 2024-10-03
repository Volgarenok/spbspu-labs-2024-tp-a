#include "DataStruct.hpp"

namespace kumekova {

void printHex(std::ostream& stream, const unsigned long long value) {
    stream << std::uppercase << std::hex << std::showbase
           << value
           << std::nouppercase << std::dec << std::noshowbase;
}

std::istream& operator>>(std::istream& stream, DataStruct& dataStruct) {
    std::string line;
    std::getline(stream, line);

    size_t from = line.find(':');
    if (from == std::string::npos) {
        stream.setstate(std::ios::failbit);
        return stream;
    }

    for (size_t i = 0; i < 3; ++i) {
        ++from;
        const auto to = line.find(':', from);
        if (to == std::string::npos) {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        std::string part(line.c_str() + from, to - from);
        if (part == "key1") {
            from = to;
            const auto valueFrom = line.find(':', from);
            if (valueFrom == std::string::npos) {
                stream.setstate(std::ios::failbit);
                return stream;
            }
            std::string valueStr(line.c_str() + valueFrom + 1);
            if (valueStr.size() > 2 && valueStr[0] == '0' && (valueStr[1] == 'x' || valueStr[1] == 'X')) {
                valueStr = valueStr.substr(2);
                try {
                    dataStruct.key1 = std::stoull(valueStr, nullptr, 16);
                } catch (const std::invalid_argument& e) {
                    stream.setstate(std::ios::failbit);
                    return stream;
                }
            } else {
                try {
                    dataStruct.key1 = std::stoull(valueStr, nullptr, 10);
                } catch (const std::invalid_argument& e) {
                    stream.setstate(std::ios::failbit);
                    return stream;
                }
            }
        } else if (part == "key2") {
            from = to;
            const auto valueFrom = line.find(':', from);
            if (valueFrom == std::string::npos) {
                stream.setstate(std::ios::failbit);
                return stream;
            }
            std::string valueStr(line.c_str() + valueFrom + 1);
            if (valueStr.size() > 2 && valueStr[valueStr.size() - 2] == 'u' && valueStr[valueStr.size() - 1] == 'l') {
                valueStr = valueStr.substr(0, valueStr.size() - 2);
                try {
                    dataStruct.key2 = std::stoull(valueStr, nullptr, 10);
                } catch (const std::invalid_argument& e) {
                    stream.setstate(std::ios::failbit);
                    return stream;
                }
            } else {
                try {
                    dataStruct.key2 = std::stoull(valueStr, nullptr, 10);
                } catch (const std::invalid_argument& e) {
                    stream.setstate(std::ios::failbit);
                    return stream;
                }
            }
        } else if (part == "key3") {
            from = to;
            const auto valueFrom = line.find(':', from);
            if (valueFrom == std::string::npos) {
                stream.setstate(std::ios::failbit);
                return stream;
            }
            std::string valueStr(line.c_str() + valueFrom + 1);
            dataStruct.key3 = valueStr;
        }
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct) {
    stream << "(:key1 ";
    if (dataStruct.key1 != 0) {
        stream << "0x";
    }
    printHex(stream, dataStruct.key1);
    stream << " " << dataStruct.key2 << " " << dataStruct.key3;
    return stream;
}

bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1) {
        return lhs.key1 < rhs.key1;
    } else if (lhs.key2 != rhs.key2) {
        return lhs.key2 < rhs.key2;
    } else {
        return lhs.key3 < rhs.key3;
    }
}

}
