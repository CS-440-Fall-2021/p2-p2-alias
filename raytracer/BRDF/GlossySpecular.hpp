#pragma once 

#include "BRDF.hpp"

class GlossySpecular : public BRDF{
    
    private:
        float ks;
        RGBColor cs;
        float exp;
    
    public:
        // Constructors.
        GlossySpecular() = default;
        GlossySpecular(float ks_, RGBColor cs_, float exp_);

        // Destructor.
        ~GlossySpecular() = default;

        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;

        // Access Methods.
        virtual void set_ks(const float _ks);
        virtual void set_cs(const RGBColor& _cs);
        virtual void set_exp(const float _exp);
        virtual float get_ks() const;
        virtual RGBColor get_cs() const;
};