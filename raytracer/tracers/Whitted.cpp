#include "Whitted.hpp"

Whitted::Whitted(): Tracer() {
}
		
Whitted::Whitted(World* _worldPtr): Tracer(_worldPtr){
}

RGBColor Whitted::trace_ray(const Ray ray, const int depth) {
	if (depth > world->vplane.max_depth)
		return(black);
	else {
		ShadeInfo sr(world->hit_objects(ray));    
					
		if (sr.hit) {
			sr.depth = depth;
			sr.ray = ray;	
			return (sr.material_ptr->shade(sr));   
		}
		else
			return (world->bg_color);
	}																																			
}
