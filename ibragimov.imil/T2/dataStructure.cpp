#include "dataStructure.hpp"

#include <iomanip>
#include <tuple>
#include "delimiters.hpp"
#include "inputFormatters.hpp"
#include "streamGuard.hpp"

std::istream& ibragimov::operator>>(std::istream& in, DataStructure& value)
{
  using namespace ibragimov;
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    int keysAmount = 3;
    bool isInputed[3] = {false, false, false};
    int keyId = 0;
    in >> std::noskipws;
    in >> DelimiterI{"("};
    while ((in) && (keysAmount != 0))
    {
      in >> DelimiterI{":key"} >> keyId;
      if ((keyId == 1) && (isInputed[keyId - 1] == false))
      {
        in >> DoubleLitI{value.key1};
      }
      else if ((keyId == 2) && (isInputed[keyId - 1] == false))
      {
        in >> ComplexLspI{value.key2};
      }
      else if ((keyId == 3) && (isInputed[keyId - 1] == false))
      {
        in >> StringI{value.key3};
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      isInputed[keyId - 1] = true;
      --keysAmount;
    }
    in >> DelimiterI{":)"};
  }
  return in;
}

std::ostream& ibragimov::operator<<(std::ostream& out, const DataStructure& value)
{
  using namespace ibragimov;
  out << std::fixed << std::setprecision(1);
  out << "(:key1 " << value.key1 << "d";
  out << ":key2 " << "#c(" << value.key2.real() << ' ' << value.key2.imag() << ")";
  out << ":key3 " << std::quoted(value.key3) << ":)";
  return out;
}

bool ibragimov::operator<(const DataStructure& l, const DataStructure& r) {
  double lComplex = std::abs(l.key2);
  double rComplex = std::abs(r.key2);
  size_t lStr = l.key3.size();
  size_t rStr = r.key3.size();
  return std::tie(l.key1, lComplex, lStr) < std::tie(r.key1, rComplex, rStr);
}

bool ibragimov::operator==(const DataStructure& l, const DataStructure& r) {
  return (!(l < r) && !(r < l));
}
