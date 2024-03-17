#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <iostream>

namespace namestnikov
{
  struct DataStruct
  {
  public:
    DataStruct(double key1, unsigned long long key2, std::string key3);
    double get_key1() const;
    unsigned long long get_key2() const;
    std::string get_key3() const;
  private:
    double key1_;
    unsigned long long key2_;
    std::string key3_;
  };
  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
  std::istream & operator>>(std::istream & in, std::string & s);
}
#endif