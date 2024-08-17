#include "polygon.hpp"

int main()
{
  altun::Point one(0, 0);
  altun::Point two(0, 1);
  altun::Point three(1, 0);
  altun::Polygon poly;
  poly.points.push_back(one);
  poly.points.push_back(two);
  poly.points.push_back(three);

}

