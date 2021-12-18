#pragma once

#include "Light.hpp"

class AmbientLight : public Light{
    private:
        float ls;
        RGBColor color;

    public:
        AmbientLight();
        AmbientLight(float l, RGBColor col);
        
        AmbientLight(const AmbientLight &other) = default;
        AmbientLight &operator=(const AmbientLight &rhs) = default;

        ~AmbientLight() = default;

        virtual Vector3D get_direction(ShadeInfo& si);
        virtual RGBColor L(ShadeInfo& si);
};