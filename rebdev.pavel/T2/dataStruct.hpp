#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

namespace rebdev
{
  struct DataStruct
  {
    unsigned long long key1_;
    unsigned long long key2_;
    std::string key3_;

    bool operator<(const DataStruct & rhv) const;
    bool operator>(const DataStruct & rhv) const;

  };

  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);

  std::istream & operator>>(std::istream & in, std::string & str);
}

#endif
