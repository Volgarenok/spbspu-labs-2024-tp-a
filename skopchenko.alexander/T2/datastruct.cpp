#include "datastruct.h"
#include <iostream>
#include <regex>

namespace skopchenko
{

  std::istream& operator>>(std::istream& is, DataStruct& data)
  {
    std::string line;
    std::getline(is, line);
    std::regex pattern(R"(\(:key1 #c\(([-+]?\d+\.\d+) ([-+]?\d+\.\d+)\):key2 \(:N ([-+]?\d+):D (\d+)\):key3 "(.+?)":\))");    std::smatch match;

    if (std::regex_search(line, match, pattern))
    {
      data.key1 = {std::stod(match[1]), std::stod(match[2])};
      data.key2 = {std::stoll(match[3]), std::stoull(match[4])};
      data.key3 = match[5];
    }

    return is;
  }

  std::ostream& operator<<(std::ostream& os, const DataStruct& data)
  {
    os << "(:key1 #c(" << data.key1.real() << " " << data.key1.imag() << "):"
       << "key2 (:N " << data.key2.first << ":D " << data.key2.second << "):"
       << "key3 \"" << data.key3 << "\":)";
    return os;
  }

  bool compare(const DataStruct& a, const DataStruct& b)
  {
    if (a.key1.real() != b.key1.real())
    {
      return a.key1.real() < b.key1.real();
    }
    if (a.key1.imag() != b.key1.imag())
    {
      return a.key1.imag() < b.key1.imag();
    }
    if (a.key2.first != b.key2.first)
    {
      return a.key2.first < b.key2.first;
    }
    if (a.key2.second != b.key2.second)
    {
      return a.key2.second < b.key2.second;
    }
    return a.key3 < b.key3;
  }

}
