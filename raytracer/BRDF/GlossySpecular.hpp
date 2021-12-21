#pragma once 

#include "BRDF.hpp"

class GlossySpecular : public BRDF{
    
    private:
        double ks;
        RGBColor cs;
        double exp;
    
    public:
        // Constructors.
        GlossySpecular() = default;
        GlossySpecular(double ks_, RGBColor cs_, double exp_);

        // Destructor.
        ~GlossySpecular() = default;

        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo, double& pdf) const;
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;

        // Access Methods.
        virtual void set_ks(const double _ks);
        virtual void set_cs(const RGBColor& _cs);
        virtual void set_exp(const double _exp);
        virtual double get_ks() const;
        virtual RGBColor get_cs() const;
};