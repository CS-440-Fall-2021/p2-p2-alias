#include "Point3D.hpp"

Point3D::Point3D(){ // set point to (0, 0, 0).
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D(float c){ // set point to (c, c, c).
    x = c;
    y = c;
    z = c;
}

Point3D::Point3D(float _x, float _y, float _z){ // set point to (x,y,z).
    x = _x;
    y = _y;
    z = _z;
}

  
std::string Point3D::to_string() const{ 
    // String representation.
    // X-coordinate: x
    // Y-coordinate: y
    // Z-coordinate: z
    std::string out = "X-coordinate:" + std::to_string(x) + "\n" +
                        "Y-coordinate:" + std::to_string(y) + "\n" +
                        "Z-coordinate:" + std::to_string(z) + "\n";
    
    return out;
}

Point3D Point3D::operator-() const{  // unary minus (-this)
    return Point3D(-x, -y, -z);
}

Vector3D Point3D::operator-(const Point3D &p) const{ // vector joining two points
    return Vector3D(x-p.x, y-p.y, z-p.z);
}

Point3D Point3D::operator+(const Vector3D &v) const{ // addition of a vector
    return Point3D(x+v.x, y+v.y, z+v.z);
}

Point3D Point3D::operator-(const Vector3D &v) const{ // subtraction of a vector
    return Point3D(x-v.x, y-v.y, z-v.z);
}

Point3D Point3D::operator*(const float s) const{ // scale the point by a factor, s.
    return Point3D(x*s, y*s, z*s);
}    

float Point3D::d_squared(const Point3D &p) const{ // square of distance
    // (this - p) is the distance vector
    return (*this - p).len_squared();
}

float Point3D::distance(const Point3D &p) const{ // distance
    // (this - p) is the distance vector
    return (*this - p).length();
}

// Scale pt by a factor, s.
Point3D operator*(const float a, const Point3D &pt){
    return pt * a;
}

// Point3D min(const Point3D& a, const Point3D& b){
//     // comparing on the basis of distance from origin
//     return a.distance(Point3D()) < b.distance(Point3D()) ? a : b;
// }

// Point3D max(const Point3D& a, const Point3D& b){
//     // comparing on the basis of distance from origin
//     return a.distance(Point3D()) > b.distance(Point3D()) ? a : b;
// }

// Compare points.
Point3D min(const Point3D& a, const Point3D& b){
    float minX;
    float minY;
    float minZ;

    if (a.x <= b.x){
        minX = a.x;
    }
    else{
        minX = b.x;
    }
    if (a.y <= b.y){
        minY = a.y;
    }
    else{
        minY = b.y;
    }
    if (a.z <= b.z){
        minZ = a.z;
    }
    else{
        minZ = b.z;
    }

    return Point3D(minX, minY, minZ);
}

Point3D max(const Point3D& a, const Point3D& b){
    float maxX;
    float maxY;
    float maxZ;

    if (a.x >= b.x){
        maxX = a.x;
    }
    else{
        maxX = b.x;
    }
    if (a.y >= b.y){
        maxY = a.y;
    }
    else{
        maxY = b.y;
    }
    if (a.z >= b.z){
        maxZ = a.z;
    }
    else{
        maxZ = b.z;
    }

    return Point3D(maxX, maxY, maxZ);
}