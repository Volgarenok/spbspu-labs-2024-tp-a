#include <map>
#include "ERDictionary.hpp"

namespace kozakova
{
  void insert(std::map< std::string, ERDictionary >& dicts, std::istream& in);
  void search(const std::map< std::string, ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void remove(std::map< std::string, ERDictionary >& dicts, std::istream& in);
  void removeTranslation(std::map< std::string, ERDictionary >& dicts, std::istream& in);
  void searchShort(const std::map< std::string, ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void searchSame(const std::map< std::string, ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void defineIdentical(const std::map< std::string, ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void combine(std::map< std::string, ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void getIntersection(std::map< std::string, ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void save(const std::map< std::string, ERDictionary >& dicts, const std::string& fname);
}
