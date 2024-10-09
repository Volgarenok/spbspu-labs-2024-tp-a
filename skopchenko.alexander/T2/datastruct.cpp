#include "datastruct.h"
#include "delimiter.h"
#include "format.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>

namespace skopchenko
{

  std::istream &operator>>(std::istream &is, DataStruct &data)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }

    std::string inputLine;
    std::getline(is, inputLine);

    //std::regex validPattern(R"(\(:key1\s#c\([-+]?[0-9]*\.?[0-9]+\s[-+]?[0-9]*\.?[0-9]+\):key2\s\(:N\s-?[0-9]+:D\s[0-9]+\):key3\s\".*\"\))");
    std::regex validPattern(R"(\(:key1\s#c\([-+]?[0-9]*\.?[0-9]+\s[-+]?[0-9]*\.?[0-9]+\):key2\s\(:N\s-?[0-9]+:D\s[0-9]+\):key3\s\".*\"\))");



    if (!std::regex_match(inputLine, validPattern))
    {
      is.setstate(std::ios::failbit);
      return is;
    }

    std::istringstream iss(inputLine);
    using del = Delimiter;
    iss >> del{"("};
    const size_t KEYS = 3;
    for (size_t i = 0; i < KEYS; ++i)
    {
      size_t key = 0;
      iss >> del{":key"} >> key;
      if (key == 1)
      {
        double real_part = 0.0, imag_part = 0.0;
        iss >> DblLit{real_part} >> DblLit{imag_part};
        data.key1 = std::complex<double>(real_part, imag_part);
      }
      else if (key == 2)
      {
        long long first_part = 0;
        unsigned long long second_part = 0;
        iss >> first_part >> UllOct{second_part};
        data.key2 = std::make_pair(first_part, second_part);
      }
      else if (key == 3)
      {
        iss >> StringVal{data.key3};
      }
      else
      {
        iss.setstate(std::ios::failbit);
        return is;
      }
    }
    iss >> del{":)"};
    return is;
  }


/*  std::ostream &operator<<(std::ostream &os, const DataStruct &data)
  {
    os << std::fixed << std::setprecision(1)
       << "(:key1 #c(" << data.key1.real() << " " << data.key1.imag() << "):"
       << "key2 (:N " << data.key2.first << ":D " << data.key2.second << "):"
       << "key3 \"" << data.key3 << "\")";
    return os;
  }*/
  std::ostream &operator<<(std::ostream &os, const DataStruct &data)
  {
    os << std::fixed << std::setprecision(1)
       << "(:key1 #c(" << data.key1.real() << " " << data.key1.imag() << "):"
       << "key2 (:N " << data.key2.first << ":D " << data.key2.second << "):"
       << "key3 \"" << data.key3 << "\")";
    return os;
  }


  bool compare(const DataStruct &a, const DataStruct &b)
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
    return a.key3.size() < b.key3.size();
  }

}
