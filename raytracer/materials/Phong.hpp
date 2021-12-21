#pragma once

#include "Material.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../BRDF/GlossySpecular.hpp"

class Phong: public Material{
    public:
        // Constructors
        Phong(void);
        Phong(Lambertian* , Lambertian* , GlossySpecular*);
        virtual RGBColor shade(ShadeInfo& sr) override;
        // Access Methods
        virtual void set_ks(const double ks);
        virtual void set_cs(const double cs);
        virtual void set_ka(const double ka);
        virtual void set_kd(const double kd);
        virtual void set_cd(const RGBColor& c);
        virtual void set_exp(const double exp);

    protected:
        Lambertian* ambient_brdf;
        Lambertian* diffuse_brdf;
        GlossySpecular* specular_brdf;
};