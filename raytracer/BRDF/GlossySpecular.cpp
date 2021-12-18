#include "GlossySpecular.hpp"

RGBColor GlossySpecular::f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const {
    RGBColor L; 
    float ndotwi = sr.normal * wi;
    Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
    float rdotwo = r * wo;

    if (rdotwo > 0.0)
        L = ks * pow(rdotwo, exp);
    
    return (L);
}