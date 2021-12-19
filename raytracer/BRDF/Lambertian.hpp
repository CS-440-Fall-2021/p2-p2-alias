#pragma once 

#include "BRDF.hpp"
#include "../utilities/Constants.hpp"

class Lambertian{
    
    private:
        float kd;
        RGBColor cd;
    
    public:

        // Constructors.
        Lambertian() = default;
        Lambertian(float kd_, RGBColor cd_);

        // Destructor.
        ~Lambertian() = default;

        RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo, float& pdf);
        RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;

        // Access Methods.
        void set_kd(const float _kd);
        void set_cd(const RGBColor& _cd);
        float get_kd() const;
        RGBColor get_cd() const;
};