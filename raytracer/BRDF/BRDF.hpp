#pragma once 

#include "../samplers/Sampler.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/RGBColor.hpp"

class ShadeInfo;

class BRDF{
    protected:
        Sampler *sampler_ptr;
        Vector3D normal;
    
    public:
        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const = 0;
        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo) const = 0;
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const = 0;
};