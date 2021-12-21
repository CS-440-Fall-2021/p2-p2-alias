#include "GlossySpecular.hpp"
#include <math.h>

GlossySpecular::GlossySpecular(double ks_, RGBColor cs_, double exp_){
    ks = ks_;
    cs = cs_;
    exp = exp_;
}

RGBColor GlossySpecular::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const {
    RGBColor L; 
    double ndotwi = sr.normal * wi;
    Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
    double rdotwo = r * wo;

    if (rdotwo > 0.0)
        L = ks * pow(rdotwo, exp);
    
    return (L);
}

RGBColor GlossySpecular::sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo, double& pdf) const {
    double ndotwo = sr.normal * wo;
    Vector3D r = -wo + 2.0 * sr.normal * ndotwo; // direction of mirror
                                                    // reflection
    Vector3D w = r;
    Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;

    Point3D sp = sampler_ptr->sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w; // reflected ray direction
    
    if (sr.normal * wi < 0.0) // reflected ray is below surface
        wi = -sp.x * u - sp.y * v + sp.z * w;

    double phong_lobe = pow(r * wi, exp);
    pdf = phong_lobe * (sr.normal * wi);

    return (ks * cs * phong_lobe);
}

RGBColor GlossySpecular::rho(const ShadeInfo& sr, const Vector3D& wo) const{
    return RGBColor(); // return black color
}

void GlossySpecular::set_ks(const double _ks){
    ks = _ks;
}

void GlossySpecular::set_cs(const RGBColor& _cs){
    cs = _cs;
}

void GlossySpecular::set_exp(const double _exp){
    exp = _exp;
}

double GlossySpecular::get_ks() const{
    return ks;
}

RGBColor GlossySpecular::get_cs() const{
    return cs;
}