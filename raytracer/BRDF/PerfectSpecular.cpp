#include "PerfectSpecular.hpp"

RGBColor PerfectSpecular::sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo) const {
    float ndotwo = sr.normal * wo;
    wi = -wo + 2.0 * sr.normal * ndotwo;
    return (kr * cr / (sr.normal * wi));
}

RGBColor PerfectSpecular::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const{
    return RGBColor(); // return black color
}

RGBColor PerfectSpecular::rho(const ShadeInfo& sr, const Vector3D& wo) const{
    return RGBColor(); // return black color
}