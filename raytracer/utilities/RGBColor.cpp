#include "RGBColor.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>

RGBColor::RGBColor(){
    r = 0;
    g = 0;
    b = 0;
}

RGBColor::RGBColor(float c){
    r = c;
    g = c;
    b = c;

    clamp();
}

RGBColor::RGBColor(float _r, float _g, float _b){
    r = _r;
    g = _g;
    b = _b;
}

std::string RGBColor::to_string() const{
    std::string out = std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b) + "\n";

    return out;
}               

RGBColor RGBColor::operator+(const RGBColor &c) const{
    return RGBColor(r+c.r, g+c.g, b+c.b).clamp();
    
}

RGBColor &RGBColor::operator+=(const RGBColor &c){
    r = r+c.r;
    g = g+c.g;
    b = b+c.b;
    clamp();
    return *this;
}

RGBColor RGBColor::operator*(const float a) const{
    return RGBColor(r*a, g*a, b*a).clamp();
}

RGBColor &RGBColor::operator*=(const float a){
    *this = RGBColor(r*a, g*a, b*a).clamp();
    return *this;
}

RGBColor RGBColor::operator/(const float a) const{
    return RGBColor(r/a, g/a, b/a).clamp();
}

RGBColor &RGBColor::operator/=(const float a){
    *this = RGBColor(r/a, g/a, b/a).clamp();
    return *this;
}

RGBColor RGBColor::operator*(const RGBColor &c) const{
    return RGBColor(r*c.r, g*c.g, b*c.b).clamp();
}

bool RGBColor::operator==(const RGBColor &c) const{
    return ((r==c.r) & (g==c.g) & (b==c.b));
}

RGBColor RGBColor::powc(float p) const{
    return RGBColor(pow(r, p), pow(g, p), pow(b, p)).clamp();
}

float RGBColor::average() const{
    return (r+g+b)/3;
}

RGBColor RGBColor::clamp(){
    float _r = std::max((float)0, std::min(r, (float)1));
    float _g = std::max((float)0 , std::min(g, (float)1));
    float _b = std::max((float)0 , std::min(b, (float)1));
    
    return RGBColor(_r, _g, _b);
}

RGBColor operator*(const float a, const RGBColor &c){
    return c * a;
}
