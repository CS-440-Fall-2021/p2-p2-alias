#include "RGBColor.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>

RGBColor::RGBColor(){
    r = 0;
    g = 0;
    b = 0;
}

RGBColor::RGBColor(double c){
    r = c;
    g = c;
    b = c;

    clamp();
}

RGBColor::RGBColor(double _r, double _g, double _b){
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

RGBColor RGBColor::operator*(const double a) const{
    return RGBColor(r*a, g*a, b*a).clamp();
}

RGBColor &RGBColor::operator*=(const double a){
    *this = RGBColor(r*a, g*a, b*a).clamp();
    return *this;
}

RGBColor RGBColor::operator/(const double a) const{
    return RGBColor(r/a, g/a, b/a).clamp();
}

RGBColor &RGBColor::operator/=(const double a){
    *this = RGBColor(r/a, g/a, b/a).clamp();
    return *this;
}

RGBColor RGBColor::operator*(const RGBColor &c) const{
    return RGBColor(r*c.r, g*c.g, b*c.b).clamp();
}

bool RGBColor::operator==(const RGBColor &c) const{
    return ((r==c.r) & (g==c.g) & (b==c.b));
}

RGBColor RGBColor::powc(double p) const{
    return RGBColor(pow(r, p), pow(g, p), pow(b, p)).clamp();
}

double RGBColor::average() const{
    return (r+g+b)/3;
}

RGBColor RGBColor::clamp(){
    double _r = std::max((double)0, std::min(r, (double)1));
    double _g = std::max((double)0 , std::min(g, (double)1));
    double _b = std::max((double)0 , std::min(b, (double)1));
    
    return RGBColor(_r, _g, _b);
}

RGBColor operator*(const double a, const RGBColor &c){
    return c * a;
}
