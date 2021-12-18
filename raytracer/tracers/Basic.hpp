#pragma once

#include "Tracer.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../materials/Material.hpp"

class Basic : public Tracer {
    public:
        Basic();
        Basic(World *w);

        Basic(const Basic&) = default;
        Basic &operator=(const Basic&) = default;

        RGBColor trace_ray(const Ray &ray, const int depth);
};