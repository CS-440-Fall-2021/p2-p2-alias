#include "Phong.hpp"

Phong::Phong(){
    ambient_brdf = nullptr;
    diffuse_brdf = nullptr;
    specular_brdf = nullptr;

}

Phong::Phong(Lambertian* amb, Lambertian* dif, GlossySpecular* spec){
    ambient_brdf = amb;
    diffuse_brdf = dif;
    specular_brdf = spec;
}


RGBColor Phong::shade(ShadeInfo& sr) {
    Vector3D wo = -sr.ray.d;
    RGBColor L = ambient_brdf->rho(sr, wo) * sr.w->ambient_ptr->L(sr);
    int num_lights = sr.w->lights.size();

    for (int j = 0; j < num_lights; j++) {
        Vector3D wi = sr.w->lights[j]->get_direction(sr);
        float ndotwi = sr.normal * wi;

        if (ndotwi > 0.0) 
            L += ( diffuse_brdf->f(sr, wi, wo) + 
            specular_brdf->f(sr, wi, wo)) * sr.w->lights[j]->L(sr) * ndotwi;
    }

    return (L);
}