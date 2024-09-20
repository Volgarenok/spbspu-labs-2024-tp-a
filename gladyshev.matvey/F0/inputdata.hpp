#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <istream>
#include <fstream>
#include <string>
#include <map>

namespace gladyshev
{
  using dic = std::map< std::string, int >;
  using mainDic = std::map< std::string, dic >;
  void makeDict(mainDic& finres, std::ifstream& file, std::istream& in);
  void makeDictLen(mainDic& finres, std::ifstream& file, std::istream& in);
}

#endif
