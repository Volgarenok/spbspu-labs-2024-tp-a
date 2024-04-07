#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <cstddef>
#include <string>

namespace vyzhanov
{
  struct DataStruct
  {
    DataStruct(size_t key1, size_t key2, std::string key3);
  private:
    size_t key1_;
    size_t key2_;
    std::string key3_;
  };
}

#endif
