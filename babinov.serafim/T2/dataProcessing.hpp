#ifndef DATA_PROCESSING_HPP
#define DATA_PROCESSING_HPP
#include <istream>
#include "dataStruct.hpp"

namespace babinov
{
  struct DataProcessor
  {
    DataProcessor(DataStruct& data):
     dataStruct(data)
    {}
   private:
    DataStruct dataStruct;
  };
  std::istream& operator>>(std::istream& in, DataProcessor& proc);
}

#endif
