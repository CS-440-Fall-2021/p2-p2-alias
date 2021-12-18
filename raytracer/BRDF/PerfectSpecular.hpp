#pragma once 

#include "BRDF.hpp"

class PerfectSpecular{
    
    private:
        float kr;
        RGBColor cr;
    
    public:
        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;

        // Access Methods.
        void set_kr(const float _kr);
        void set_cr(const RGBColor& _cr);
        float get_kr() const;
        RGBColor get_cr() const;
};