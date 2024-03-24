#include "DataStruct.h"

petrov::DataStruct::DataStruct(long long key1, unsigned long long key2, const std::string& key3):
  key1_(key1),
  key2_(key2),
  key3_(key3)
{
}
bool petrov::DataStruct::operator<(const DataStruct& other) const
{
  if (!(key1_ == other.key1_))
  {
    return key1_ < other.key1_;
  }
  if (!(key2_ == other.key2_))
  {
    return key2_ < other.key2_;
  }
  return key3_.length() < other.key3_.length();
}