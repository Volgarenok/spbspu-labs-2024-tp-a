#include "cmds.hpp"

void skuratov::cmd1(const int&, std::ostream& out)
{
  out << "Hi, this is CMD1" << '\n';
}
void skuratov::cmd2(const int&, std::ostream& out)
{
  out << "Hi, this is CMD2" << '\n';
}
void skuratov::cmd3(int&, std::ostream& out)
{
  out << "Hi, this is CMD3" << '\n';
}
void skuratov::cmd4(std::ostream& out)
{
  out << "Hi, this is CMD4" << '\n';
  throw std::overflow_error{ "Overflow cmd4" };
}
