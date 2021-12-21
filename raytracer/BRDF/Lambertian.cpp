#include "Lambertian.hpp"

RGBColor Lambertian::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const{
    return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeInfo& sr, const Vector3D& wo) const{
    return (kd * cd);
}

RGBColor Lambertian::sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo, double& pdf){
    return RGBColor();
}

void Lambertian::set_kd(const double _kd){
    kd = _kd;
}

void Lambertian::set_cd(const RGBColor& _cd){
    cd = _cd;
}

double Lambertian::get_kd() const{
    return kd;
}

RGBColor Lambertian::get_cd() const{
    return cd;
}

Lambertian::Lambertian(double kd_, RGBColor cd_){
    kd = kd_;
    cd = cd_;
}