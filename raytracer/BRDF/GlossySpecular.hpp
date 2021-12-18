#pragma once 

#include "BRDF.hpp"

class GlossySpecular{
    
    private:
        float ks;
        float exp;
    
    public:
        virtual RGBColor f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo);
};