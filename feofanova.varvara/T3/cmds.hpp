#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <vector>
#include "polygon.hpp"

namespace feofanova
{
	void getArea(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);

	void Perms(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
}
#endif