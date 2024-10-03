#include "DataStruct.hpp"

namespace kumekova {

namespace {

constexpr size_t KeyCount = 3;
constexpr size_t KeyLength = 4;
constexpr size_t SpaceLength = 1;
constexpr size_t PrefixLength = 2;
constexpr size_t SuffixLength = 3;

bool parse(const std::string& part, DataStruct& dataStruct) {
    constexpr auto ValueOffset = KeyLength + SpaceLength;

    const auto partLength = part.size();
    if (partLength < ValueOffset) {
        return false;
    }

    const std::string keyStr(part.data(), KeyLength);
    const std::string valueStr(part.data() + ValueOffset, partLength - ValueOffset);

    if (keyStr == "key3") {
        dataStruct.key3 = valueStr;
        return true;
    }

    const auto valueLength = valueStr.size();

    if (keyStr == "key2") {
        if (valueLength > SuffixLength &&
            valueStr[valueLength - SuffixLength] == 'u' &&
            valueStr[valueLength - SuffixLength + 1] == 'l' &&
            valueStr[valueLength - SuffixLength + 2] == 'l') {
            const auto trimmed = valueStr.substr(0, valueLength - SuffixLength);
            try {
                dataStruct.key2 = std::stoull(trimmed, nullptr, 0);
                return true;
            } catch (const std::invalid_argument& e) {
                // Handle the error, e.g., return false or throw an exception
                return false;
            }
        }
    }

    if (keyStr == "key1") {
        if (valueLength > PrefixLength &&
            (valueStr[0] == '0' && (valueStr[1] == 'x' || valueStr[1] == 'X'))) {
            const auto trimmed = valueStr.substr(2);
            try {
                dataStruct.key1 = std::stoull(trimmed, nullptr, 16);
                return true;
            } catch (const std::invalid_argument& e) {
                // Handle the error, e.g., return false or throw an exception
                return false;
            }
        } else {
            try {
                dataStruct.key1 = std::stoull(valueStr, nullptr, 10);
                return true;
            } catch (const std::invalid_argument& e) {
                // Handle the error, e.g., return false or throw an exception
                return false;
            }
        }
    }

    return false;
}

void printHex(std::ostream& stream, const unsigned long long value) {
    stream << std::uppercase << std::hex << std::showbase
           << value
           << std::nouppercase << std::dec << std::noshowbase;
}

} // namespace

std::istream& operator>>(std::istream& stream, DataStruct& dataStruct) {
    constexpr auto NoPos = std::string::npos;
    constexpr auto FailBit = std::ios::failbit;

    std::string line;
    std::getline(stream, line);

    size_t from = line.find(':');
    if (from == NoPos) {
        stream.setstate(FailBit);
        return stream;
    }

    for (size_t i = 0; i < KeyCount; ++i) {
        ++from;
        const auto to = line.find(':', from);
        if (to == NoPos || !parse(std::string(line.c_str() + from, to - from), dataStruct)) {
            stream.setstate(FailBit);
            return stream;
        }
        from = to;
    }
    stream >> dataStruct.key1 >> dataStruct.key2 >> dataStruct.key3;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct) {
    stream << "(:key1 ";
    if (dataStruct.key1 != 0) {
        stream << "0x";
    }
    printHex(stream, dataStruct.key1);
    stream << dataStruct.key1 << " " << dataStruct.key2 << " " << dataStruct.key3;
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

} // namespace kumekova
