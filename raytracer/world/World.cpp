#include "World.hpp"

World::World(){
    camera_ptr = NULL;
    sampler_ptr = NULL;
    std::vector<Geometry *> geometry;

}

World::~World(){
    
    
}

void World::add_geometry(Geometry *geom_ptr){
    geometry.push_back(geom_ptr);
}
void World::set_camera(Camera *c_ptr){
    camera_ptr = c_ptr;
}


ShadeInfo World::hit_objects(const Ray &ray){
    ShadeInfo sf(*this);
    sf.t = kHugeValue;
    for (const auto &g: geometry){
        if (g->hit(ray,sf.t,sf)) //if the ray hits the object
        {
            // update the following values of shadeinfo:
            sf.hit=true;
            sf.material_ptr=g->get_material();
            sf.ray=ray;
        }
    }
    sf.normal.normalize();
    sf.ray.d.normalize();
    return sf;
}