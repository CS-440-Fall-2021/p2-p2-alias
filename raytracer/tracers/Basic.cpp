#include "Basic.hpp"
#include <iostream>

Basic::Basic(): Tracer() {
}

Basic::Basic(World* w): Tracer(w) {
}

RGBColor Basic::trace_ray(const Ray &ray, const int depth){
    RGBColor pixel_color(0);

    double weight = ray.w; // ray weight for the pixel.
    // std::cout << "Here Me out ;-;\n";
    ShadeInfo sinfo = world->hit_objects(ray);
    if (sinfo.hit) {
        pixel_color += weight * sinfo.material_ptr->shade(sinfo);
    }
    else {
        pixel_color += weight * world->bg_color;
    }

    return pixel_color;
}