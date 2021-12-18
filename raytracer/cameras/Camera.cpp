#include "Camera.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"

Camera::Camera(): eye(), lookat(), up(), exposure_time(1.0){
}

Camera::Camera(Point3D eye_, Point3D lookat_, Vector3D up_): eye(eye_), lookat(lookat_), 
                                                            up(up_), exposure_time(1.0) {
}

Camera::Camera(Point3D eye_, Point3D lookat_, Vector3D up_, float expos_time): eye(eye_), lookat(lookat_), 
                                                            up(up_), exposure_time(expos_time) {
}

Vector3D Camera::ray_direction(const Point3D &p) const{return Vector3D();}

Vector3D Camera::ray_direction(const Point3D& pixel_point, 
                                const Point3D& lens_point) const{return Vector3D();}


void Camera::compute_uvw(){
    w = lookat - eye;
    w.normalize();
    u = up ^ w;
    u.normalize();
    v = w ^ u;
}