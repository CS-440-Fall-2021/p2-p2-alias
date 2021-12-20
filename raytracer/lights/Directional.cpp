#include "Directional.hpp"

Directional::Directional(): ls(1), color(1), dir(){
}

Directional::Directional(float l, RGBColor col, Vector3D dir): ls(l), color(col), dir(dir){
}

Vector3D Directional::get_direction(ShadeInfo &si){
    return -dir;
}

RGBColor Directional::L(ShadeInfo &si) {
    return (ls * color);
}