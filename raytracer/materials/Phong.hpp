#pragma once

#include "Material.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../BRDF/GlossySpecular.hpp"

class Phong: public Material{
    public:
        Phong(void);
        Phong(Lambertian* , Lambertian* , GlossySpecular*);
        virtual RGBColor shade(ShadeInfo& sr);
    protected:
        Lambertian* ambient_brdf;
        Lambertian* diffuse_brdf;
        GlossySpecular* specular_brdf;
};