#include "figures.h"
#include <cmath>

float Point::distance(const Point &other) const
{
    return sqrt(pow(x() - other.x(), 2)	+ pow(y() - other.y(), 2));
}