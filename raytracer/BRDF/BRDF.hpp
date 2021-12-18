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
        // Constructors.
        BRDF();
        BRDF(Sampler *sampler_ptr_, Vector3D normal_);

        // Copy constuctor and assignment operator.
        BRDF(const BRDF &brdf) = default;
        BRDF &operator=(const BRDF &other) = default;

        // Desctructor.
        virtual ~BRDF() = default;

        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;
};