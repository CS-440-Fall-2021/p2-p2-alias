#include "Vector3D.hpp"
#include <math.h>

Vector3D::Vector3D(){
    x = 0;
    y = 0;
    z = 0;
}

Vector3D::Vector3D(double c){
    x = c;
    y = c;
    z = c;
}

Vector3D::Vector3D(double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}

Vector3D::Vector3D(const Point3D &p){
    x = p.x;   
    y = p.y;   
    z = p.z;   
}


std::string Vector3D::to_string() const{
    std::string out = "X-component:" + std::to_string(x) + "\n" +
                        "Y-component:" + std::to_string(y) + "\n" +
                        "Z-component:" + std::to_string(z) + "\n";
    
    return out;
}


Vector3D Vector3D::operator-() const{
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator+(const Vector3D &v) const{
    return Vector3D(x+v.x, y+v.y, z+v.z);
}

Vector3D &Vector3D::operator+=(const Vector3D &v){
    *this = Vector3D(x+v.x, y+v.y, z+v.z);
    return *this;
} 

Vector3D Vector3D::operator-(const Vector3D &v) const{
    return Vector3D(x-v.x, y-v.y, z-v.z);
}

Vector3D Vector3D::operator-=(const Vector3D &v){
    *this = Vector3D(x-v.x, y-v.y, z-v.z);
    return *this;
} 


Vector3D Vector3D::operator*(const double a) const{
    return Vector3D(x*a, y*a, z*a);
}

Vector3D Vector3D::operator/(const double a) const{
    return Vector3D(x/a, y/a, z/a);
}

void Vector3D::normalize(){
    if (length() > 0)
        *this = *this/length();
} 


double Vector3D::length() const{
    return sqrt(x*x + y*y + z*z);
}

double Vector3D::len_squared() const{
    return x*x + y*y + z*z;
}


double Vector3D::operator*(const Vector3D &b) const{
    return x*b.x + y*b.y + z*b.z;
}

Vector3D Vector3D::operator^(const Vector3D &v) const{
    return Vector3D(y*v.z - z*v.y, 
                    z*v.x - x*v.x, 
                    x*v.y - y*v.x);
}


Vector3D operator*(const double a, const Vector3D &v){
    return v*a;
}

