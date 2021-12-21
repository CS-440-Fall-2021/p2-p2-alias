#pragma once 

#include "BRDF.hpp"

class PerfectSpecular{
    
    private:
        double kr;
        RGBColor cr;
    
    public:

        // Constructors.
        PerfectSpecular() = default;
        PerfectSpecular(double kr_, RGBColor cr_);

        // Destructor.
        ~PerfectSpecular() = default;

        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor f(const ShadeInfo& sr, const Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor rho(const ShadeInfo& sr, const Vector3D& wo) const;

        // Access Methods.
        void set_kr(const double _kr);
        void set_cr(const RGBColor& _cr);
        double get_kr() const;
        RGBColor get_cr() const;
};