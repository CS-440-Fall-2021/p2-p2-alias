#pragma once

#include "Geometry.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <string>
#include <iostream>

#include <limits>
#define inf std::numeric_limits<double>::infinity()

class Rectangle  : public Geometry {
protected:
	
  Point3D 		p0;   			// corner vertex 
  Vector3D		a;				// side
  Vector3D		b;				// side

  Vector3D normal;
  double a_len_squared;
  double b_len_squared;

public:
  // Constructors.
  Rectangle();
  Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Vector3D n);

  // Copy constructor and assignment operator.
  Rectangle (const Rectangle &object) = default;
  Rectangle &operator=(const Rectangle &rhs) = default;

  // Destructor.
  virtual ~Rectangle() = default;
  
  // String representation.
  virtual std::string to_string() const override;

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, double &t, ShadeInfo &s) const override;
  Rectangle *clone() const;
  
  // Get bounding box.
  virtual BBox getBBox() const override;
};