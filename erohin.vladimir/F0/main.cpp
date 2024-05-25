#include <iostream>
#include <string>
#include <map>

enum numformat_t
{
  NUMBER,
  PROPORTION,
  FRACTIONAL,
  PERCENTAGE
};

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  std::string format_arg(argv[1]);
  numformat_t used_numformat;
  if (format_arg.substr(0, 12) == "--numformat=")
  {
    std::map< std::string, numformat_t > format;
    format["NUMBER"] = NUMBER;
    format["PROPORTION"] = PROPORTION;
    format["FRACTIONAL"] = FRACTIONAL;
    format["PERCENTAGE"] = PERCENTAGE;
    used_numformat = format[format_arg.substr(12)];
  }
  else
  {
    std::cerr << "Wrong number format\n";
    return 2;
  }
  return 0;
}
