#ifndef DATASTRUCT
#define DATASRUCT
#include<string>

namespace kozakova {
  struct DataStruct
  {
    unsigned long long get_Key1() const
    {
      return key1;
    }
    unsigned long long get_Key2() const
    {
      return key2;
    }
    std::string get_Key3() const
    {
      return key3;
    }
    void set_Key1(const unsigned long long k1)
    {
      key1 = k1;
    }
    void set_Key2(const unsigned long long k2)
    {
      key2 = k2;
    }
    void set_Key3(const std::string k3)
    {
      key3 = k3;
    }
    bool operator<(const DataStruct& value) const;
  private:
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}
#endif
