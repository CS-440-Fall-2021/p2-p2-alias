
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
#include "../tracers/Whitted.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/MultiJittered.hpp"

#include "../lights/Directional.hpp"
#include "../lights/AmbientLight.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"

#include <iostream>

/*
From behind Mewtwo:
  Eye: 0,0,700
  At: 0,0,-200
  Plane : top-left : -220, 220, 600
          bottom-right : 220, -220, 600
  d : 100

*/




void
World::build(void) {
  vplane.top_left.x = -220; 
  vplane.top_left.y = 220;
  vplane.top_left.z = 600;
  vplane.bottom_right.x = 220;
  vplane.bottom_right.y = -220;
  vplane.bottom_right.z = 600;
  vplane.hres = 1000;
  vplane.vres = 1000;
  vplane.max_depth = 2;

  tracer_ptr = new Whitted(this);
  Acceleration* g_ptr = new Acceleration(50, 50, 50);

  ambient_ptr = new AmbientLight(0.4, RGBColor(0.1,0.1,0.1));
  Light *directional = new Directional(1.0, white, Vector3D(0.01, -1, -1)); 
  Light *directional1 = new Directional(1.0, white, Vector3D(0.01, -1, -1)); 
  add_light(directional);
  add_light(directional1);
    
  bg_color = black;  // background color.

  // camera and sampler.
  Camera *cam = new Pinhole(Point3D(0,0,700), Point3D(0,0,-200), 100);
  cam->compute_uvw();
  set_camera(cam);
  sampler_ptr = new Simple(cam, &vplane);
  sampler_ptr = new MultiJittered(10);
  sampler_ptr->set_num_sets(vplane.get_hres() * vplane.get_vres());
  sampler_ptr->generate_samples();
  sampler_ptr->map_samples_to_hemisphere(10);
  set_acceleration(g_ptr);


  // load_OBJ("C:\\Users\\abbas\\3D Objects\\Intergalactic_Spaceship-(Wavefront).obj");
  // load_OBJ("C:\\Users\\abbas\\3D Objects\\cube.obj");
  // load_OBJ("D:\\moid\\p2-p2-alias\\assets\\PokeScene.obj");
  load_scene("D:\\moid\\p2-p2-alias\\assets\\Scene.ply", true);
  // add_obj("../assets/PokeBall.obj", new Cosine(blue));
  g_ptr->setup_cells();
  std::cout << "set up\n";
  add_geometry(g_ptr);

  // vertical plane
  Plane* plane_ptr = new Plane(Point3D(0, 0, -660), Vector3D(0, 0, 1));
  plane_ptr->set_material(new Cosine(RGBColor(0.70, 0.7, 0.7)));
  add_geometry(plane_ptr);


  std::cout << "Bounding box" << g_ptr->getBBox().to_string() << std::endl;
}

