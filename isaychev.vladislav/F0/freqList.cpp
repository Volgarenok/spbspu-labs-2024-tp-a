#include "freqList.hpp"

void isaychev::FreqList::insert(const Word & rhs)
{
  auto result = list.insert({rhs, 1});
  if (!result.second)
  {
    (*result.first).second += 1;
  }
}
