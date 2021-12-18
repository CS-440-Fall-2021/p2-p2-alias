#pragma once 

#include "BRDF.hpp"
#include "../utilities/Constants.hpp"

class Lambertian{
    
    private:
        float kd;
        RGBColor cd;
    
    public:
        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        // virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo);
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;
};