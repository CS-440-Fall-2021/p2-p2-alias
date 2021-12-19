#include "PointLight.hpp"

PointLight::PointLight(): ls(1), color(1), location(){
}

PointLight::PointLight(float l, RGBColor col, Vector3D loc): ls(l), color(col), location(loc){
}

Vector3D PointLight::get_direction(ShadeInfo &si){
    return (location - si.hit_point).hat();
}

RGBColor PointLight::L(ShadeInfo &si) {
    return (ls * color);
}

void PointLight::set_location(const float x, const float y, const float z){
    location = Vector3D(x,y,z);
}

void PointLight::scale_radiance(const float f){
    ls = f;
}