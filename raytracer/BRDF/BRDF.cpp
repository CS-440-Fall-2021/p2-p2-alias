#include "BRDF.hpp"

BRDF::BRDF(): 
    sampler_ptr(NULL), 
    normal()
{}

BRDF::BRDF(Sampler *sampler_ptr_, Vector3D normal_){
    sampler_ptr = sampler_ptr_;
    normal = normal_;
}

RGBColor BRDF::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const {return RGBColor();}
RGBColor BRDF::sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo) const {return RGBColor();}
RGBColor BRDF::rho(const ShadeInfo& sr, const Vector3D& wo) const {return RGBColor();}