#include <istream>
#include <ostream>
#include <string>
#include <iomanip>

#include "DataStruct.hpp"
#include "Delimiter.hpp"

std::istream& ayupov::operator>>(std::istream& in, DataStruct& value){
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> DelimiterChar{'('};
  int keyNum = 0;
  for (int i = 0; i < 3; i++){
    in >> StringI{":key"} >> keyNum;
    if (keyNum == 1){
      in >> DblSciI{value.key1};
    }
    else if (keyNum == 2){
      in >> DelimiterChar({'\''}) >> value.key1 >> DelimiterChar({'\''});
    }
    else if (keyNum == 3){
      std::getline(in >> DelimiterChar{'"'}, value.key3, '\"');
    }
    else{
      in.setstate(std::ios::failbit);
    }
  }
  in >> StringI{":)"};
  return in;
}
std::ostream& ayupov::operator<<(std::ostream& out, const DataStruct& value){
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:key1 ";
  int e = 0;
  double dblOut = value.key1;
  while (dblOut >= 10.0){
    e++;
    dblOut /= 10.0;
  }
  while (dblOut < 1.0){
    e--;
    dblOut *= 10.0;
  }
  out << std::setprecision(2) << dblOut << 'e' << e;
  out << ":key2 '" << value.key2 << '\'';
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}
bool ayupov::DataStruct::operator<(const DataStruct &other) const{
  if (key1 == other.key1){
    if (key2 == other.key2){
      return key3.size() < key3.size();
    }
    return key2 < other.key2;
  }
  return key1 < other.key1;
}
