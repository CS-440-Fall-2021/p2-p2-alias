#pragma once

#include "Camera.hpp"
#include "../utilities/Image.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../tracers/Tracer.hpp"
#include "../samplers/Sampler.hpp"
#include "../materials/Material.hpp"

class Pinhole: public Camera{
    private:
        float d;
        float zoom;

    public:
        Pinhole();
        Pinhole(Point3D eye, Point3D lookat, float d_);
        Pinhole(Point3D eye, Point3D lookat, Vector3D up, 
                float exposure_time, float d, float zoom);

        Pinhole(const Pinhole &other) = default;
        Pinhole &operator=(const Pinhole &rhs) = default;

        ~Pinhole() = default;

        Vector3D ray_direction(const Point3D &p) const;
        void render_scene(World &w);
};