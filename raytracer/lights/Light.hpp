#pragma once 

#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"

class Light{
    protected:
        bool shadows;
    public:
        // Constructors.
        Light() = default; // does nothing.

        // Copy constuctor and assignment operator.
        Light(const Light &camera) = default;
        Light &operator=(const Light &other) = default;

        // Desctructor.
        virtual ~Light() = default;

        virtual Vector3D get_direction(ShadeInfo& si) = 0;
        virtual RGBColor L(ShadeInfo& si) = 0;
};