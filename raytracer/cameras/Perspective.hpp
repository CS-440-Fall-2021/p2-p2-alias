#pragma once

/**
   This file declares the Perspective class which represents a perspective
   viewing camera.

   Courtesy Kevin Suffern.
*/

#include "Camera.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"

class Vector3D;

class Perspective : public Camera {
protected:
  Point3D pos; // center of projection.

public:
  // Constructors.
  Perspective();                          // set pos to origin.
  Perspective(double c);                   // set pos to (c, c, c).
  Perspective(double x, double y, double z); // set pos to (x, y, z)
  Perspective(const Point3D &pt);         // set pos parallel to pt.

  // Copy constuctor and assignment operator.
  Perspective(const Perspective &camera);
  Perspective &operator=(const Perspective &other);

  // Desctructor.
  virtual ~Perspective() = default;

  // Get direction of projection for a point.
  virtual Vector3D get_direction(const Point3D &p) const;
};
