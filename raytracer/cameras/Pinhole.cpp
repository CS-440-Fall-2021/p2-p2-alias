#include "Pinhole.hpp"
#include <iostream>

Pinhole::Pinhole(): Camera(), d(0), zoom(1){
}

Pinhole::Pinhole(Point3D eye, Point3D lookat, double d_): Camera(eye, lookat, Vector3D()),
                                                        d(d_){
}

Pinhole::Pinhole(Point3D eye, Point3D lookat, Vector3D up, 
    double exposure_time, double d_, double zoom_): Camera(eye, lookat, up),
                                                d(d_), zoom(zoom_){
}

Vector3D Pinhole::ray_direction(const Point3D &p) const {
    Vector3D dir = p.x * u + p.y * v - d * w;
    return dir.hat();
}

void Pinhole::render_scene(World &w){
    Sampler *sampler = w.sampler_ptr;
    ViewPlane &viewplane = w.vplane;
    Image image(viewplane);

    std::vector<Ray> rays;

    for (int x = 0; x < viewplane.hres; x++) {   // across.
        for (int y = 0; y < viewplane.vres; y++) { // down.
            // Get rays for the pixel from the sampler. The pixel color is the
            // weighted sum of the shades for each ray.
            RGBColor pixel_color(0);

            rays = sampler->get_rays(x, y);
            // std::cout << rays[0].to_string();
            for (const auto &ray : rays) {
                pixel_color += w.tracer_ptr->trace_ray(ray, 0);
            }
            // Save color to image.
            image.set_pixel(x, y, pixel_color);
        }
    }

    // Ray ray;
    // int depth = 0;  
    // Point3D pp;		// sample point on a pixel
    // int n = (int) sqrt( (double) sampler->get_num_samples());

	// ray.o = eye;
		
	// for (int r = 0; r < viewplane.vres; r++)			// up
	// 	for (int c = 0; c < viewplane.hres; c++) {		// across 					
	// 		RGBColor L = black; 
			
	// 		for (int p = 0; p < n; p++)			// up pixel
	// 			for (int q = 0; q < n; q++) {	// across pixel
	// 				double h = (viewplane.bottom_right.x - viewplane.top_left.x) / viewplane.hres;
    //                 double v = (viewplane.top_left.y - viewplane.bottom_right.y) / viewplane.vres;
                    
    //                 // computing the position of the ray
    //                 pp.x = viewplane.top_left.x + h * (c + 0.5);
    //                 pp.y = viewplane.top_left.y - v * (r + 0.5);
	// 				ray.d = ray_direction(pp);
	// 				L += w.tracer_ptr->trace_ray(ray, depth);
	// 			}	
											
	// 		// L /= sampler->get_num_samples();
	// 		// L *= exposure_time;
    //         image.set_pixel(c, r, L);
	// 	} 


    // Write image to file.
    image.write_ppm("scene.ppm");
    
    std::cout << "Scene Rendered";

}