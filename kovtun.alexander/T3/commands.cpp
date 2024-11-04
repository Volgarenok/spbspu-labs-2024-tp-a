#include "commands.hpp"


void kovtun::area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out)
{
    for (int i = 0; i < polygons.size(); i++)
    {
        out << "area: " << kovtun::getArea(polygons[i]) << "\n";
    }
}
