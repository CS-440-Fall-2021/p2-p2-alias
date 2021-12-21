#pragma once

#include "Phong.hpp"
#include "../BRDF/PerfectSpecular.hpp"
#include "../tracers/Tracer.hpp"

class Reflective: public Phong {
    private:
        PerfectSpecular* reflective_brdf;   

    public:
        // constructors, access functions, etc.
        Reflective();
        Reflective(PerfectSpecular*);
        Reflective(Lambertian* amb, Lambertian* dif, GlossySpecular* spec, PerfectSpecular*);

        ~Reflective() = default;

        virtual RGBColor shade(ShadeInfo& sr) override;   

        // Access Methods 
        void set_kr(const double kr);
        void set_cr(const RGBColor cr);
};