#pragma once

/**
   This file declares the Triangle class which represents a triangle defined by
   its 3 vertices.

   Courtesy Kevin Suffern.
*/
#include <math.h>

#include "Geometry.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"

class Triangle : public Geometry {
protected:
  Point3D v0, v1, v2; // the vertices. they must not be colinear.
  Vector3D n0, n1, n2;

public:
  // Constructors. Passed vertices are assumed to be ordered for orientation,
  Triangle(); // triangle with vertices at origin.
  Triangle(const Point3D &, const Point3D &, const Point3D &, const Vector3D&); // set vertices.
  Triangle(const Point3D &, const Point3D &, const Point3D &, const Vector3D&, const Vector3D&, const Vector3D&); // set vertices.

  // Copy constructor and assignment operator.
  Triangle(const Triangle &object);
  Triangle &operator=(const Triangle &rhs);

  // Destructor.
  virtual ~Triangle() = default;

  // String representation.
  std::string to_string() const override;

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, double &t, ShadeInfo &s) const override;
  Triangle *clone() const;
  Vector3D interpolate_normals(double, double) const;

  // Get bounding box.
  virtual BBox getBBox() const override;
};
