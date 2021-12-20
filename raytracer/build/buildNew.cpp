
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
  vplane.top_left.x = -220;
  vplane.top_left.y = 220;
  vplane.top_left.z = 500;
  vplane.bottom_right.x = 220;
  vplane.bottom_right.y = -220;
  vplane.bottom_right.z = 500;
  vplane.hres = 1000;
  vplane.vres = 1000;

  tracer_ptr = new Basic(this);
  Acceleration* g_ptr = new Acceleration(50, 50, 50);
    
    
  bg_color = black;  // background color.

  // camera and sampler.
  Camera *cam = new Pinhole(Point3D(0, 0, 600), Point3D(0, 0, -200), 100);
  cam->compute_uvw();
set_camera(cam);
  sampler_ptr = new Simple(camera_ptr, &vplane);
  set_acceleration(g_ptr);


  // load_OBJ("C:\\Users\\abbas\\3D Objects\\Intergalactic_Spaceship-(Wavefront).obj");
  // load_OBJ("C:\\Users\\abbas\\3D Objects\\cube.obj");
  load_OBJ("../assets/PokeScene.obj");
  // add_obj("../assets/PokeBall.obj", new Cosine(blue));
  g_ptr->setup_cells();
  add_geometry(g_ptr);

  // vertical plane
  // Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Vector3D(0, 0, 1));
  // plane_ptr->set_material(new Cosine(green));
  // add_geometry(plane_ptr);


  std::cout << "Bounding box" << g_ptr->getBBox().to_string() << std::endl;
}

