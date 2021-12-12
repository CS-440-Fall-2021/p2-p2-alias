#include "Ray.hpp"

Ray::Ray(){
    o = Point3D(0);
    d = Vector3D(0);
    w = 1;
} 

Ray::Ray(const Point3D &origin, const Vector3D &dir){
    o = origin;
    d = dir;
    d.normalize();
    w = 1;
}

std::string Ray::to_string() const{
    std::string out = "Origin: " + o.to_string() + "\n" +
                        "Direction: " + d.to_string() + "\n";
    return out;
}