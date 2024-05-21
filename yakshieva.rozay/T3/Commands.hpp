#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "Polygon.hpp"
 
namespace yakshieva
{
	// править аргументы под один
	void doAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
	void doMaxCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
	void doMinCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
	void doCountCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
	void doLessAreaCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
	void doRmechoCommand(std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
	void doEchoCommand(std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
}
#endif