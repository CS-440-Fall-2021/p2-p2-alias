#include "Cosine.hpp"
#include <iostream>
#include <math.h>

Cosine::Cosine(){
    color = RGBColor(0);
}

Cosine::Cosine(double c){
    color = RGBColor(c);    
}

Cosine::Cosine(double r, double g, double b){
    color = RGBColor(r, g, b);    

}

Cosine::Cosine(const RGBColor &c){
    color = c;
}

Cosine::Cosine(const Cosine &other){
    color = other.color;
}
Cosine &Cosine::operator=(const Cosine &other){
    color = other.color;
    return *this;
}

RGBColor Cosine::shade(ShadeInfo &sinfo){
    RGBColor r = color * (sinfo.normal * (-sinfo.ray.d));
    return r;
}
