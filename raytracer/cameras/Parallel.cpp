#include "Parallel.hpp"

Parallel::Parallel(){
    dir = Vector3D(0, 0, -1);
}

Parallel::Parallel(double c){
    dir = Vector3D(c,c,c);
    dir.normalize();
}

Parallel::Parallel(double x, double y, double z){
    dir = Vector3D(x,y,z);
    dir.normalize();
}

Parallel::Parallel(const Vector3D &d){
    dir = d;
    dir.normalize();
}

Parallel::Parallel(const Parallel &camera){
    dir = camera.dir;
    dir.normalize();
}

Parallel &Parallel::operator=(const Parallel &other){
    dir = other.dir;
    dir.normalize();
    return *this;
};

// Get direction of projection for a point.
Vector3D Parallel::get_direction(const Point3D &p) const{
    return dir;
}