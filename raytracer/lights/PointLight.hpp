#pragma once

#include "Light.hpp"

class PointLight : public Light{
    private:
        float ls;
        RGBColor color;
        Vector3D location;

    public:
        PointLight();
        PointLight(float l, RGBColor col, Vector3D loc);
        
        PointLight(const PointLight &other) = default;
        PointLight &operator=(const PointLight &rhs) = default;

        ~PointLight() = default;

        virtual Vector3D get_direction(ShadeInfo& si);
        virtual RGBColor L(ShadeInfo& si);

        // Access Methods
        void set_location(const float x, const float y, const float z);
        void scale_radiance(const float f);
};