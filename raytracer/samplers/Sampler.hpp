#pragma once

/**
   This file declares the Sampler class which is an abstract class for concrete
   samplers to inherit from.

   A sampler samples a scene by shooting primary rays through pixels in a
   viewplane. A primary ray begins at the pixel and its direction is determined
   by a camera. Different samplers shoot different numbers of primary rays in
   different manners.

   Courtesy Kevin Suffern.
*/

#include <vector>
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../world/ViewPlane.hpp"
#include "../cameras/Camera.hpp"
#include "../utilities/Ray.hpp"

class Camera;
class Ray;
class ViewPlane;

class Sampler {
protected:
  Camera *camera_ptr;       // the camera that decides the projectors.
  ViewPlane *viewplane_ptr; // the view plane through which rays are shot.
  int num_samples;     		// the number of sample points in a set
  int num_sets;				// the number of sample sets
  std::vector<Point3D> samples;				// sample points on a unit square
	int jump;					// random index jump
	long unsigned count;					// random index jump
	std::vector<int> shuffled_indices;		// shuffled samples array indices
	std::vector<Point3D> hemisphere_samples;		// sample points on a unit hemisphere



public:
  // Constructors.
  Sampler();                                // initializes members to NULL.
  Sampler(int num_samples);     // initializes number of samples.
  Sampler(Camera *c_ptr, ViewPlane *v_ptr); // set members.

  // Copy constuctor and assignment operator.
  Sampler(const Sampler &camera) = default;
  Sampler &operator=(const Sampler &other) = default;

  // Desctructor.
  virtual ~Sampler() = default;

  // Get rays corresponding to a pixel in the view plane. px and py are 0-based
  // indexes of the pixel in the view plane, with the origin at the top left of
  // the view plane.
  virtual std::vector<Ray> get_rays(int px, int py) const;

  void set_num_samples(int nsm);
  void set_num_sets(int ns);
  void setup_shuffled_indices();
  virtual void generate_samples() = 0;
  int get_num_samples();

  virtual Point3D sample_hemisphere();
  void map_samples_to_hemisphere(const double p);
};
