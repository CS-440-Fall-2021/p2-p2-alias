#include "Perspective.hpp"

Perspective::Perspective(){
    pos = Point3D();
}   

Perspective::Perspective(double c){
    pos = Point3D(c);
}

Perspective::Perspective(double x, double y, double z){
    pos = Point3D(x,y,z);
}

Perspective::Perspective(const Point3D &pt){
    pos = pt;
}

Perspective::Perspective(const Perspective &camera){
    pos = camera.pos;
}

Perspective &Perspective::operator=(const Perspective &other){
    pos = other.pos;
    return *this;
}

Vector3D Perspective::get_direction(const Point3D &p) const{
    Vector3D a = (p - pos);
    a.normalize();
    return a;
}