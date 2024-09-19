#include "format.h"
#include "streamguard.h"

namespace skopchenko {

  std::istream& operator>>(std::istream& in, DblLit&& key) {
    std::istream::sentry guard(in);
    if (!guard) {
      return in;
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, UllOct&& key)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    skopchenko::StreamGuard streamGuard(in);
    return in;
  }

}