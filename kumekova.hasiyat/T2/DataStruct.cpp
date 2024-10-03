#include <algorithm>
#include <tuple>

#include "DataStruct.hpp"

namespace kumekova
{
    std::istream& operator>>(std::istream& stream, DataStruct& dataStruct)
    {
        char c;
        std::string token;
        stream >> c;
        if (c != '(') {
            stream.setstate(std::ios::failbit);
            throw std::runtime_error("Invalid input format: expected '('");
        }

        while (stream >> token) {
            if (token == "key1") {
                if (token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
                    stream >> std::hex >> dataStruct.key1;
                } else {
                    stream.setstate(std::ios::failbit);
                    throw std::runtime_error("Invalid input format: expected hexadecimal or decimal value for key1");
                }
            } else if (token == "key2") {
                unsigned long long ull;
                stream >> ull;
                if ((token[0] == 'u' && token[1] == 'l' && token[2] == 'l')|| (token[0] == 'U' && token[1] == 'L' && token[2] == 'L')) {
                    stream >> std::hex >> dataStruct.key2;
                } else {
                    stream.setstate(std::ios::failbit);
                    throw std::runtime_error("Invalid input format: expected hexadecimal or decimal value for key2");
                }
            } else if (token == "key3") {
                stream >> c;
                if (c != '"') {
                    stream.setstate(std::ios::failbit);
                    throw std::runtime_error("Invalid input format: expected '\"'");
                }
                std::getline(stream, dataStruct.key3, '"');
            }
           
        }
        if (stream.peek() == '\n' || stream.peek() == '\r') {
            stream.setstate(std::ios::failbit);
            throw std::runtime_error("Invalid input format: empty string");
        }
        return stream;
	};

	std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct) {
        stream << "(" << "key1 " << dataStruct.key1 << ":key2 '" << dataStruct.key2 << "':key3 \"" << dataStruct.key3 << "\"";
        return stream;
	};

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
