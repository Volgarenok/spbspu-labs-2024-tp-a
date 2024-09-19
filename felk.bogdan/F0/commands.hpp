#include <iostream>
#include <unordered_map>

namespace felk
{
  using Dict = std::unordered_map< std::string, size_t >;
  void makeDict(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void split(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void setNewNumber(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void getMean(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void clear(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void filter(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void print(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void getUnique(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void lenFilter(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);
  void deleteKey(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >&);

}
