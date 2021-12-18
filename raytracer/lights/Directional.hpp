#pragma once

#include "Light.hpp"

class Directional : public Light{
    protected:
        float ls;
        RGBColor color;
        Vector3D dir;

    public:
        Directional();
        Directional(float l, RGBColor col, Vector3D dir);
        
        Directional(const Directional &other) = default;
        Directional &operator=(const Directional &rhs) = default;

        ~Directional() = default;

        virtual Vector3D get_direction(ShadeInfo& si);
        virtual RGBColor L(ShadeInfo& si);
};