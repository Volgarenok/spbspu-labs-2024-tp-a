#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <stdexcept>

enum numformat_t
{
  NUMBER,
  PROPORTION,
  FRACTIONAL,
  PERCENTAGE
};

std::ostream & print_numformat(std::ostream & output, size_t number, size_t size, numformat_t format)
{
  if (format == NUMBER)
  {
    output << number;
  }
  else if (format == PROPORTION)
  {
    output << number << " / " << size;
  }
  else if (format == FRACTIONAL)
  {
    output << std::setprecision(6) << std::fixed << static_cast< double >(number) / size;
  }
  else if (format == PERCENTAGE)
  {
    output << std::setprecision(6) << std::fixed << static_cast< double >(number) / size * 100 << " %";
  }
  return output;
}

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  std::string format_arg(argv[1]);
  numformat_t used_numformat = NUMBER;
  if (format_arg.substr(0, 12) == "--numformat=")
  {
    std::map< std::string, numformat_t > format;
    format["NUMBER"] = NUMBER;
    format["PROPORTION"] = PROPORTION;
    format["FRACTIONAL"] = FRACTIONAL;
    format["PERCENTAGE"] = PERCENTAGE;
    try
    {
      used_numformat = format.at(format_arg.substr(12));
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "Wrong number format\n";
      return 2;
    }
    print_numformat(std::cout, 1, 25, used_numformat);
  }
  else
  {
    std::cerr << "Wrong CLA to identify numformat\n";
    return 3;
  }
  return 0;
}
