#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP
namespace sakovskaia
{
  std::istream & operator>>(std::istream & input, unsigned long long key);
  std::istream & operator>>(std::istream & input, char key);
  std::istream & operator>>(std::istream & input, std::string key);
}
#endif
