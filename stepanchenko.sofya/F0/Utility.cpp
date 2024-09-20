#include "Utility.hpp"

#include <list>

void stepanchenko::checkName(std::vector< CrossRefs >& cross_refs, const std::string& name)
{
  auto iter = std::find_if(cross_refs.begin(), cross_refs.end(), [&](CrossRefs& cr) {
  return cr.getName() == name;
  });
  if (iter != cross_refs.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void stepanchenko::printL(const std::pair < size_t, std::string >& line, std::ostream& out)
{
  out << line.first << ' ' << line.second << '\n';
}

void stepanchenko::writeToFile(const std::vector< std::pair< size_t, std::string > >& lines, std::ofstream& file)
{
  for (const auto& line : lines)
  {
    file << line.first << ": " << line.second << "\n";
  }
}

void stepanchenko::swapLines(const std::vector< std::pair< size_t, std::string > >::iterator first,
	const std::vector< std::pair< size_t, std::string > >::iterator second, bool pred)
{
  if (pred)
  {
    std::iter_swap(first, second);
  }
}
