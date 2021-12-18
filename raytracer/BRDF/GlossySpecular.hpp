#pragma once 

#include "BRDF.hpp"

class GlossySpecular{
    
    private:
        float ks;
        float exp;
    
    public:
        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
};