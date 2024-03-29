#include "dataStructure.hpp"

#include "delimiter.hpp"
#include "inputFormatters.hpp"
#include "outputFormatters.hpp"

std::istream& ibragimov::operator>>(std::istream& in, DataStructure& value)
{
  using namespace ibragimov;
  std::istream::sentry guard(in);
  if (guard)
  {
    int keysAmount = 3;
    bool isInputed[3] = {false, false, false};
    int keyId = 0;
    in >> CharDelimiterI{'('};
    while ((in) && (keysAmount != 0))
    {
      in >> CharDelimiterI{':'} >> KeyIdI{keyId};
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
    in >> CharDelimiterI{':'} >> CharDelimiterI{')'};
  }
  return in;
}

std::ostream& ibragimov::operator<<(std::ostream& out, const DataStructure& value)
{
  using namespace ibragimov;
  out << "(:key1 " << DoubleLitO{value.key1};
  out << ":key2 " << ComplexLspO{value.key2};
  out << ":key3 " << StringO{value.key3} << ":)";
  return out;
}
