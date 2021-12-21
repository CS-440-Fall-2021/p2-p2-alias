#pragma once

#include "Light.hpp"

class PointLight : public Light{
    private:
        double ls;
        RGBColor color;
        Vector3D location;

    public:
        PointLight();
        PointLight(double l, RGBColor col, Vector3D loc);
        
        PointLight(const PointLight &other) = default;
        PointLight &operator=(const PointLight &rhs) = default;

        ~PointLight() = default;

        virtual Vector3D get_direction(ShadeInfo& si);
        virtual RGBColor L(ShadeInfo& si);

        // Access Methods
        void set_location(const double x, const double y, const double z);
        void scale_radiance(const double f);
};