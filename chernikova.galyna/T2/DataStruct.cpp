#include "DataStruct.h"
#include <string>
#include <iostream>
#include "Delimiter.h"
#include "StreamGuard.h"

std::ostream& chernikova::operator<<(std::ostream& out, const DataStruct& 
value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);
  out << "(:key1 " << std::uppercase << std::scientific << value.key1;
  out << ":key2 " << std::oct << value.key2;
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}

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
