
/**
   This builds a scene that consists of 35 shaded spheres and a plane.
   Perspective viewing is used with a single sample per pixel.
   The spheres are the same as those in the Chapter 14 page one image. 

   Courtesy Kevin Suffern.
*/

#include "../acceleration/Acceleration.hpp"

#include "../cameras/Parallel.hpp"
#include "../cameras/Pinhole.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"

#include "../materials/Cosine.hpp"

#include "../tracers/Basic.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"

#include <iostream>

void
World::build(void) {
  vplane.top_left.x = -1;
  vplane.top_left.y = 1;
  vplane.top_left.z = 3;
  vplane.bottom_right.x = 1;
  vplane.bottom_right.y = -1;
  vplane.bottom_right.z = 3;
  vplane.hres = 400;
  vplane.vres = 400;

  tracer_ptr = new Basic(this);
  Acceleration* g_ptr = new Acceleration(50, 50, 50);
    
    
  bg_color = black;  // background color.

  // camera and sampler.
  Camera *cam = new Pinhole(Point3D(0, 0, 10), Point3D(0, 0, 0), 7);
  cam->compute_uvw();
  set_camera(cam);
  sampler_ptr = new Simple(camera_ptr, &vplane);
  set_acceleration(g_ptr);


  // load_OBJ("C:\\Users\\abbas\\3D Objects\\Intergalactic_Spaceship-(Wavefront).obj");
  // load_OBJ("C:\\Users\\abbas\\3D Objects\\cube.obj");
  load_OBJ("..\\assets\\PokeBall.obj");

  // vertical plane
  Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Vector3D(0, 0, 1));
  plane_ptr->set_material(new Cosine(green));
  add_geometry(plane_ptr);

  add_geometry(g_ptr);
}

