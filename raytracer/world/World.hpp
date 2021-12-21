#pragma once

/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/
// For Obj File Loading 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "../utilities/Vector3D.hpp"
#include "../geometry/Triangle.hpp"

#include <vector>

#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../geometry/Geometry.hpp"
#include "../acceleration/Acceleration.hpp"
#include "../lights/Light.hpp"
#include "ViewPlane.hpp"
#include "../utilities/Constants.hpp"
#include "../materials/Cosine.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;
class Tracer;
class Material;

class World {
public:
  ViewPlane vplane;
  RGBColor bg_color;
  std::vector<Geometry *> geometry;
  Camera *camera_ptr;
  Sampler *sampler_ptr;
  Acceleration *grid_ptr;
  Tracer *tracer_ptr;
  Acceleration* accel;
  Light* ambient_ptr;
  std::vector<Light*> lights;

public:
  // Constructors.
  World(); // initialize members.

  // Destructor.
  ~World(); // free memory.

  // Add to the scene.
  void add_geometry(Geometry *geom_ptr);
  void add_light(Light* light_ptr);
  void set_camera(Camera *c_ptr);
  void set_tracer(Tracer *t_ptr);
  void set_acceleration(Acceleration *g_ptr);

  void load_OBJ(const char* file_name);

  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build();

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  ShadeInfo hit_objects(const Ray &ray);
  void add_obj(const char *path, Material *mPtr);
  void load_scene(std::string filename, bool load_colors);
  
};
