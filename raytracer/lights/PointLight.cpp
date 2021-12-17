#include "PointLight.hpp"

PointLight::PointLight(): ls(1), color(), location(){
}

PointLight::PointLight(float l, RGBColor col, Vector3D loc): ls(l), color(col), location(loc){
}

Vector3D PointLight::get_direction(ShadeInfo &si){
    return (location - si.hit_point).hat();
}

RGBColor PointLight::L(ShadeInfo &si) {
    return (ls * color);
}