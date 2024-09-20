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
    using del = Delimiter;
    is >> del{"("};
    const size_t KEYS = 3;
    for (size_t i = 0; i < KEYS; ++i)
    {
      size_t key = 0;
      is >> del{":key"} >> key;
      if (key == 1)
      {
        // Для std::complex<double> считываем действительную и мнимую части отдельно
        double real_part, imag_part;
        is >> DblLit{real_part} >> DblLit{imag_part};
        data.key1 = std::complex<double>(real_part, imag_part);
      }
      else if (key == 2)
      {
        // Для std::pair<long long, unsigned long long> считываем два значения
        long long first_part;
        unsigned long long second_part;
        is >> first_part >> UllOct{second_part};
        data.key2 = std::make_pair(first_part, second_part);
      }
      else if (key == 3)
      {
        is >> StringVal{data.key3};
      }
      else
      {
        is.setstate(std::ios::failbit);
      }
    }
    is >> del{":)"};
    return is;
  }

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
    return a.key3 < b.key3;
  }

}
