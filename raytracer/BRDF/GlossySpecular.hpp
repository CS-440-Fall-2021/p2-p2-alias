#pragma once 

#include "BRDF.hpp"

class GlossySpecular{
    
    private:
        float ks;
        RGBColor cs;
        float exp;
    
    public:
        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;

        // Access Methods.
        void set_ks(const float _ks);
        void set_cs(const RGBColor& _cs);
        float get_ks() const;
        RGBColor get_cs() const;
};