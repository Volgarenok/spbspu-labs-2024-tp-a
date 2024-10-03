#include <algorithm>
#include <tuple>

#include "DataStruct.hpp"

namespace kumekova {
 std::istream& operator>>(std::istream& stream, DataStruct& dataStruct) {
        if (!stream) {
        throw std::runtime_error("Stream is not in a good state");
        }
        char c;
        std::string token;
        stream >> c;
        if (c != '(') {
            stream.setstate(std::ios::failbit);
            throw std::runtime_error("Invalid input format: expected '('");
        }
        while (stream >> token != ")") {
            if (token == "key1") {
                stream >> c;
                if (c == '0' && (stream.peek() == 'x' || stream.peek() == 'X')) {
                    std::string value;
                    stream >> value;
                    dataStruct.key1 = std::stol(value, 0, 16);
                } else {
                    int value;
                    stream >> value;
                    dataStruct.key1 = value;
                } 
             } else if (token == "key2") {
                    unsigned long long value;
                    stream >> value;
                    if ((stream.peek() != 'u' || stream.peek(1) != 'l' || stream.peek(2) != 'l') || (stream.peek() != 'U' || stream.peek(1) != 'L' || stream.peek(2) != 'L')) {
                        stream.setstate(std::ios::failbit);
                        throw std::runtime_error("Invalid input format: expected 'ull' suffix for key2");
                    }
                    stream.ignore(3);
                    dataStruct.key2 = value;     
            } else if (token == "key3") {
                std::string value;
                stream >> value;
                dataStruct.key3 = value;
            } else {
                 stream.setstate(std::ios::failbit);
                 throw std::runtime_error("Invalid input format: unknown key");
            }
        }
        if (!stream) {
        throw std::runtime_error("Stream is not in a good state after reading");
        }
    }

    std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct) {
        stream << "(" << "key1 " << dataStruct.key1 << ":key2 '" << dataStruct.key2 << "':key3 \"" << dataStruct.key3 << "\"";
        if (!stream) {
         throw std::runtime_error("Stream is not in a good state after reading");
        }
        return stream;
    }

    bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
        if (lhs.key1 != rhs.key1) {
            return lhs.key1 < rhs.key1;
        } else if (lhs.key2 != rhs.key2) {
            return lhs.key2 < rhs.key2;
        } else {
            return lhs.key3.size() < rhs.key3.size();
        }
    }
}
