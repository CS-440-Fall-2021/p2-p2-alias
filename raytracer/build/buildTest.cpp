#include "../world/World.hpp"
#include "../acceleration/Acceleration.hpp"
#include "../materials/Cosine.hpp"
#include "../tracers/Basic.hpp"
#include "../cameras/Pinhole.hpp"
#include "../samplers/Simple.hpp"
#include "../Geometry/Sphere.hpp"
#include "../Geometry/Plane.hpp"
#include <math.h>
#include <stdlib.h>


void World::build(void)
{   
    vplane.top_left.x = -2;
    vplane.top_left.y = 2;
    vplane.top_left.z = 3;
    vplane.bottom_right.x = 2;
    vplane.bottom_right.y = -2;
    vplane.bottom_right.z = 3;
    vplane.hres = 400;
    vplane.vres = 400;

    tracer_ptr = new Basic(this);
    Acceleration* grid_ptr = new Acceleration(50, 50, 50);
    
    
    bg_color = black;  // background color.
    
    // camera and sampler.
    Camera *cam = new Pinhole(Point3D(0, 0, 10), Point3D(0, 0, 0), 7);
    cam->compute_uvw();
    set_camera(cam);
    sampler_ptr = new Simple(camera_ptr, &vplane);
    // construct viewplane, integrator, camera, and lights
    int num_spheres = 1000000;
    float volume = 2.0 / num_spheres;
    float radius = pow(0.75 * volume / 3.14159, 0.333333);
    srand(15);
    for (int j = 0; j < num_spheres; j++)
    {
        Cosine *matte_ptr = new Cosine(RGBColor(
            static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
            static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
            static_cast <float> (rand()) / static_cast <float> (RAND_MAX)
        ));
        // matte_ptr->set_ka(0.25);
        // matte_ptr->set_kd(0.75);
        // matte_ptr->set_cd(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        //                   static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
        //                   static_cast <float> (rand()) / static_cast <float> (RAND_MAX););
        Sphere *sphere_ptr = new Sphere(Point3D(1.0 - 2.0 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                                1.0 - 2.0 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                                1.0 - 2.0 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), radius);
        
        sphere_ptr->set_material(matte_ptr);
        grid_ptr->add_object(sphere_ptr);
    }
    grid_ptr->setup_cells(); // must be called after all the
    // spheres have been added
    add_geometry(grid_ptr);
    

    RGBColor grey(0.25);  // grey
    
    // Plane* plane_ptr = new Plane(Point3D(-5, 3, 3), Vector3D(1, 0, 0));
    // plane_ptr->set_material(new Cosine(grey));
    // add_geometry(plane_ptr);
    // grid_ptr->add_object(plane_ptr);
}