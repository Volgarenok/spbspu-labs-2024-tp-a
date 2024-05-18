#include "functor.hpp"

double kuznetsov::CountAreaTriangle::operator()(const Point& third)
{
  double area = std::abs((first.x - third.x) * (second.y - third.y) - (second.x - third.x) * (first.y - third.y)) * 0.5;
  second = third;
  return area;
}
