#include "datastruct.h"
#include <iostream>
#include <regex>

namespace skopchenko
{

  std::istream& operator>>(std::istream& is, DataStruct& data)
  {
    std::string line;
    std::getline(is, line);
    std::regex pattern(R"(\(:key1 #c\(([-+]?\d*\.\d*) ([-+]?\d*\.\d*)\):key2 \(:N ([-+]?\d+):D (\d+):\):key3 "(.+?)":\))");
    std::smatch match;

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

}
