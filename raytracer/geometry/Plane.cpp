#include "Plane.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <string>
#include <iostream>

Plane::Plane(){
    n = Vector3D(0, 1.0, 0);
    a = Point3D(0);
}

Plane::Plane(const Point3D &pt, const Vector3D &n_){
    a = pt;
    n = n_;
    n.normalize();
}

Plane::Plane(const Plane &object){
    a = object.a;
    n = object.n;
    n.normalize();
}
Plane &Plane::operator=(const Plane &rhs){
    a = rhs.a;
    n = rhs.n;
    n.normalize();
    return *this;
}

  
std::string Plane::to_string() const{
    std::string out = "Point: " + a.to_string() + "\n" + 
                        "Normal: " + n.to_string() + "\n";
    return out;
}

bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const{
   // the following code is taken from the book
    double ti = (a - ray.o) * n / (ray.d * n);
    if (ti > kEpsilon && ti < t)
    {
        t=ti;
        s.normal=n;
        s.normal.normalize();
        s.hit_point= ray.o + ti * ray.d;
        s.hit = true;
        s.material_ptr = material_ptr;
        s.ray = ray;
        s.t = ti;
        return true;
    }
    else
    {
        return false;
    }
}

BBox Plane::getBBox() const{
    // TODO: getBBox for Plane
}