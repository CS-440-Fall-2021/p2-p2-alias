#include "Reflective.hpp"

Reflective::Reflective(): reflective_brdf(nullptr){
}

Reflective::Reflective(PerfectSpecular* ps): reflective_brdf(ps){    
}

Reflective::Reflective(Lambertian* amb, Lambertian* dif, GlossySpecular* spec, PerfectSpecular *ps)
    : Phong(amb, dif, spec), reflective_brdf(ps){
}


RGBColor Reflective::shade(ShadeInfo& sr) {
    RGBColor L(Phong::shade(sr)); // direct illumination
    
    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wi, wo);
    Ray reflected_ray(sr.hit_point, wi); 
    
    L += fr * sr.w->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
    
    return (L);
}

void Reflective::set_kr(const float kr){
    reflective_brdf->set_kr(kr);
}

void Reflective::set_cr(const float cr){
    reflective_brdf->set_cr(cr);
}



