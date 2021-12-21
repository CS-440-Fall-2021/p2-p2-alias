#include "AmbientLight.hpp"

AmbientLight::AmbientLight(): ls(1), color(1){
}

AmbientLight::AmbientLight(double l, RGBColor col): ls(l), color(col){
}

Vector3D AmbientLight::get_direction(ShadeInfo &si){
    return (Vector3D(0.0));
}

RGBColor AmbientLight::L(ShadeInfo &si) {
    return (ls * color);
}