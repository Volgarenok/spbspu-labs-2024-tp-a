#include "ERDictionary.hpp"

namespace kozakova
{
  void insert(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void search(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void remove(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void removeTranslation(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void searchShort(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void searchSame(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void identical(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void combine(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void intersection(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out);
  void save(const std::map< std::string, kozakova::ERDictionary >& dicts, const std::string& fname);
}
