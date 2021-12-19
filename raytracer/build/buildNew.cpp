
/**
   This builds a scene that consists of 35 shaded spheres and a plane.
   Perspective viewing is used with a single sample per pixel.
   The spheres are the same as those in the Chapter 14 page one image. 

   Courtesy Kevin Suffern.
*/

#include "../acceleration/Acceleration.hpp"

#include "../cameras/Parallel.hpp"
#include "../cameras/Pinhole.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"

#include "../materials/Cosine.hpp"

#include "../tracers/Basic.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"

#include <iostream>

void
World::build(void) {
  std::vector<Point3D> vertices;
  std::vector<Vector3D> normals;
  Acceleration *grid_ptr = new Acceleration(50, 50, 50);
}

