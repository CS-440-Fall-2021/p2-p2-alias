#pragma once

#include "../samplers/Sampler.hpp"
#include "../utilities/Image.hpp"
#include "../world/ViewPlane.hpp"
#include "../world/World.hpp"

class Tracer{
    protected:
        World *world;
    
    public:
        Tracer();
        Tracer(World *w_ptr);

        Tracer(const Tracer &tracer) = default;
        Tracer &operator=(const Tracer &other) = default;

        virtual ~Tracer() = default;

        virtual RGBColor trace_ray(const Ray &ray, const int depth) = 0;
};