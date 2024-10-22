#include "command.hpp"
#include <cmath>
#include <scopeguard.hpp>
#include "polygon.hpp"
 
namespace
{
  double calcArea(const agarkov::Point & left, const agarkov::Point & right)
  {
    return 0.5 * (left.x_ * right.y_ - right.x_ * left.y_);
  }
}