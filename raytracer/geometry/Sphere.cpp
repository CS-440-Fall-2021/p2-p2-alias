#include "Sphere.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <iostream>
Sphere::Sphere()
{
    r = 0;
    c = Point3D(0);
}

Sphere::Sphere(const Point3D &center, double radius)
{
    c = center;
    r = radius;
}

Sphere::Sphere(const Sphere &object)
{
    c = object.c;
    r = object.r;
}

Sphere &Sphere::operator=(const Sphere &rhs)
{
    c = rhs.c;
    r = rhs.r;
    return *this;
}

std::string Sphere::to_string() const
{
    std::string out = "Center: " + c.to_string() + "\n" +
                      "Radius: " + std::to_string(r) + "\n";
    return out;
}

bool Sphere::hit(const Ray &ray, double &t, ShadeInfo &s) const
{      // the following code is taken from the book
    double ti;
    // std::cout<<(ray.o - c).to_string();
    ray.o - Point3D(1);
    Vector3D temp = ray.o - this->c;
    double a = ray.d * ray.d;
    double b = 2.0 * temp * ray.d;
    double c_ = temp * temp - r * r;
    double disc = b * b - 4.0 * a * c_;
    if (disc < 0.0)
    {
        return false;
    }
    else
    {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        ti = (-b - e) / denom;

        if ((ti > kEpsilon) && (ti <= t))
        {
            t = ti;
            s.normal = (temp + ti * ray.d) / r;
            s.normal.normalize();
            s.hit_point = ray.o + ti * ray.d;
            s.hit = true;
            s.material_ptr = material_ptr;
            s.ray = ray;
            s.t = ti;
            return true;
        }
        ti = (-b + e) / denom;
        if ((ti > kEpsilon) && (ti <= t))
        {
            t = ti;
            s.normal = (temp + ti * ray.d) / r;
            s.normal.normalize();
            s.hit_point = ray.o + ti * ray.d;
            s.hit = true;
            s.material_ptr = material_ptr;
            s.ray = ray;
            s.t = ti;
            return true;
        }
    }
    return false;
}

// Get bounding box.
BBox Sphere::getBBox() const{
	Point3D PMIN = Point3D(c.x - r, c.y - r, c.z - r);
	Point3D PMAX = Point3D(c.x + r, c.y + r, c.z + r);

	return BBox(PMIN, PMAX);
}

Sphere *Sphere::clone() const{
	return (new Sphere(*this));
}