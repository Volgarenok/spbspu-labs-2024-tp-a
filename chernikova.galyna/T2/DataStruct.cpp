#include "DataStruct.h"
#include <string>
#include <iostream>
#include "Delimiter.h"
#include "StreamGuard.h"

bool chernikova::compare(const DataStruct& value1, const DataStruct& 
value2)
{
  if (value1.key1 != value2.key1)
  {
    return (value1.key1 < value2.key1);
  }
  else if (value1.key2 != value2.key2)
  {
    return (value1.key2 < value2.key2);
  }
  else
  {
    return strlen(value2.key3) < strlen(value2.key3);
  }
}
