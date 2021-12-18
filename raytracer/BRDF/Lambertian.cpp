#include "Lambertian.hpp"

RGBColor Lambertian::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const{
    return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeInfo& sr, const Vector3D& wo) const{
    return (kd * cd);
}

void Lambertian::set_kd(const float _kd){
    kd = _kd;
}

void Lambertian::set_cd(const RGBColor& _cd){
    cd = _cd;
}

float Lambertian::get_kd() const{
    return kd;
}

RGBColor Lambertian::get_cd() const{
    return cd;
}