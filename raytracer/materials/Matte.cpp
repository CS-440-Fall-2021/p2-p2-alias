#include "Matte.hpp"

RGBColor Matte::shade(const ShadeInfo& sinfo) const{
    Vector3D wo = -sinfo.ray.d;
    RGBColor L = ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_ptr->L(sinfo);
    int numLights = sinfo.w->lights.size();
    for (int j = 0; j < numLights; j++) {
        Vector3D wi = sinfo.w->lights[j]->get_direction(sinfo);
        float ndotwi = sinfo.normal * wi;
        if (ndotwi > 0.0){
            L += diffuse_brdf->f(sinfo, wo, wi) * sinfo.w->lights[j]->L(sinfo) * ndotwi;
        }
    }
    return (L);
}

Matte::Matte(Lambertian* ambient_brdf_, Lambertian* diffuse_brdf_){
    ambient_brdf = ambient_brdf_;
    diffuse_brdf = diffuse_brdf_;
}

void Matte::set_ka(const float ka){
    ambient_brdf->set_kd(ka);
}

void Matte::set_kd(const float kd){
    diffuse_brdf->set_kd(kd);
}

void Matte::set_cd(const RGBColor& c){
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}