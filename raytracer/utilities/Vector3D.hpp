#pragma once

/**
   This file declares the class Vector3D which represents a 3D vector.

   Courtesy Kevin Suffern.
*/

#include <string>
#include "Point3D.hpp"

class Point3D;

class Vector3D {
public:
  float x, y, z; // the components.

public:
  // Constructors.
  Vector3D();                                // set vector to (0, 0, 0).
  Vector3D(float c);                        // set vector to (c, c, c).
  Vector3D(float _x, float _y, float _z); // set vector to (_x, _y, _z).
  Vector3D(const Point3D &p);                // construct from a point.

  // Copy constructor and assignment operator.
  Vector3D(const Vector3D &v) = default;
  Vector3D &operator=(const Vector3D &rhs) = default;
  // Assign vector from other entitites.
  Vector3D &operator=(const Point3D &rhs); // from a point.

  // Destructor.
  ~Vector3D() = default;

  // String representation.
  std::string to_string() const;

  // Arithmetic.
  Vector3D operator-() const;                    // unary minus
  Vector3D operator+(const Vector3D &v) const;   // addition.
  Vector3D &operator+=(const Vector3D &v);       // compound addition.
  Vector3D operator-(const Vector3D &v) const;   // subtraction.
  Vector3D operator-=(const Vector3D &v);        // compound subtraction.

  // Scaling.
  Vector3D operator*(const float a) const;
  Vector3D operator/(const float a) const;
  void normalize(); // nomalize - convert to a unit vector.
  Vector3D hat() const; // return a normalized vector of this vector.

  // Length.
  float length() const;      // length.
  float len_squared() const; // square of the length.

  // Vector products.
  float operator*(const Vector3D &b) const;   // dot product.
  Vector3D operator^(const Vector3D &v) const; // cross product.
};

// Scaling.
Vector3D operator*(const float a, const Vector3D &v);
