#include "Lambertian.hpp"

RGBColor Lambertian::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const{
    return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeInfo& sr, const Vector3D& wo) const{
    return (kd * cd);
}



