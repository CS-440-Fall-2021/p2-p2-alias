#pragma once 

#include "BRDF.hpp"

class PerfectSpecular{
    
    private:
        float kr;
        RGBColor cr;
    
    public:
        virtual RGBColor sample_f(const ShadeInfo& sr, Vector3D& wi, const Vector3D& wo);
};