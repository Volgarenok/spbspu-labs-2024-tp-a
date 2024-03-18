#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <iostream>

namespace namestnikov
{
  struct DataStruct
  {
  public:
    DataStruct();
    DataStruct(double key1, unsigned long long key2, std::string key3);
    double getKey1() const;
    unsigned long long getKey2() const;
    std::string getKey3() const;
    bool operator<(const DataStruct & data) const;
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
