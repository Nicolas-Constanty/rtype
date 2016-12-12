#include <stdlib.h>
#include <cmath>
#include <iostream>

struct Vector
{
  float x;
  float y;

  Vector up(float rotation)
  {
    Vector v;

    v.x = 0;
    v.y = 1;

    std::cout << "rotating by " << rotation << std::endl;
    rotation = (rotation) * M_PI / 180.f;
    std::cout << "rotating by " << rotation << std::endl;

    v.x = cos(rotation);
    v.y = sin(rotation);
    return v;
  }
};

int main(int ac, char **av)
{
  Vector v;

  v.x = 0;
  v.y = 0;
  std::cout << "X = " << v.up(atof(av[1])).x << " Y = " << v.up(atof(av[1])).y << std::endl;
  return 0;
}
