#include "format.h"
#include "delimiter.h"
#include "streamguard.h"

namespace skopchenko
{

  std::istream &operator>>(std::istream &in, DblLit &&key)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    using Delimiter = skopchenko::Delimiter;
    in >> key.value >> Delimiter{"d"};
    return in;
  }

  std::istream &operator>>(std::istream &in, UllOct &&key)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    skopchenko::StreamGuard streamGuard(in);
    using Delimiter = skopchenko::Delimiter;
    in >> Delimiter{"0"} >> std::oct >> key.value;
    return in;
  }

  std::istream &operator>>(std::istream &in, StringVal &&key)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    using Delimiter = skopchenko::Delimiter;
    std::getline(in >> Delimiter{"\""}, key.value, '\"');  // Читаем строку между кавычками
    return in;
  }

}
