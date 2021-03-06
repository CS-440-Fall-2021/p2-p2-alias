#include "PerfectSpecular.hpp"

// Constructor
PerfectSpecular::PerfectSpecular(double kr_, RGBColor cr_){
    kr = kr_;
    cr = cr_;
}

RGBColor PerfectSpecular::sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo) const {
    double ndotwo = sr.normal * wo;
    wi = -wo + 2.0 * sr.normal * ndotwo;
    return (kr * cr / (sr.normal * wi));
}

RGBColor PerfectSpecular::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const{
    return RGBColor(); // return black color
}

RGBColor PerfectSpecular::rho(const ShadeInfo& sr, const Vector3D& wo) const{
    return RGBColor(); // return black color
}

void PerfectSpecular::set_kr(const double _kr){
    kr = _kr;
}

void PerfectSpecular::set_cr(const RGBColor& _cr){
    cr = _cr;
}

double PerfectSpecular::get_kr() const{
    return kr;
}

RGBColor PerfectSpecular::get_cr() const{
    return cr;
}