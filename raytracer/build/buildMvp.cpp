#include "../cameras/Pinhole.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/MultiJittered.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"

#include "../BRDF/Lambertian.hpp"
#include "../BRDF/GlossySpecular.hpp"
#include "../BRDF/PerfectSpecular.hpp"

#include "../lights/AmbientLight.hpp"
#include "../lights/Directional.hpp"
#include "../lights/PointLight.hpp"

#include "../tracers/Whitted.hpp"

#include "../world/World.hpp"

void World::build(void) {
  // View plane  .
  int n = 10;
  vplane.top_left.x = -n;
  vplane.top_left.y = n;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = n;
  vplane.bottom_right.y = -n;
  vplane.bottom_right.z = 10;
  vplane.hres = 1920;
  vplane.vres = 1920;
  vplane.max_depth = 10;

  grid_ptr = new Acceleration();

  tracer_ptr = new Whitted(this);

  sampler_ptr = new MultiJittered(10);
  sampler_ptr->set_num_sets(vplane.hres * vplane.vres);
  sampler_ptr->generate_samples();
  sampler_ptr->map_samples_to_hemisphere(10);

  ambient_ptr = new AmbientLight(0.4, black + 0.1);

  Light *direc = new Directional(0.99, white, Vector3D(1, 0, -1));
  add_light(direc);
  
  Light *point_l = new PointLight(0.99, white, Point3D(0, 0, 12));
  add_light(point_l);

  // colors
  RGBColor yellow(1, 1, 0);  // yellow
  RGBColor brown(0.71, 0.40, 0.16);  // brown
  RGBColor darkGreen(0.0, 0.41, 0.41);  // darkGreen
  RGBColor orange(1, 0.75, 0);  // orange
  RGBColor green(0, 0.6, 0.3);  // green
  RGBColor lightGreen(0.65, 1, 0.30);  // light green
  RGBColor darkYellow(0.61, 0.61, 0);  // dark yellow
  RGBColor lightPurple(0.65, 0.3, 1);  // light purple
  RGBColor darkPurple(0.5, 0, 1);  // dark purple
  RGBColor grey(0.3, 0.35, 0.3);  // grey
  
  // Background color.
  bg_color = grey;

  // Camera and sampler.
  set_camera(new Pinhole(Point3D(0, 0, 20), Point3D(0,0,-10), Vector3D(0,1,0), 1.0, 10, 1.0));
  camera_ptr->compute_uvw();

  for (int x = -8; x <= 8; x += 2) {
    for (int y = -8; y <= 8; y += 2) {
      Sphere* s = new Sphere(Point3D(x, y, 0), 1);
      s->set_material(new Cosine((x + 8.0) / 16.0, 0, (y + 8.0) / 16.0));
      grid_ptr->add_object(s);
    }
  }

  Sphere *s = new Sphere(Point3D(0,0,2), 3);

  Lambertian *amb = new Lambertian(0.2, yellow);
  Lambertian *diff = new Lambertian(0.9, yellow);
  GlossySpecular *gs = new GlossySpecular(0.2, white, 200);
  PerfectSpecular *ps = new PerfectSpecular(0.9, yellow);

  s->set_material(new Reflective(amb, diff, gs, ps));
  grid_ptr->add_object(s);
  grid_ptr->setup_cells();
  add_geometry(grid_ptr);
}
