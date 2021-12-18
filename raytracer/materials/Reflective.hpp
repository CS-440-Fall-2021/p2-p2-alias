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

    ~Reflective() = default;

    virtual RGBColor shade(ShadeInfo& sr);    
};