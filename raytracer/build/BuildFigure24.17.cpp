// Reference: Ray tracing from the ground up by Kevin Suffern

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.

// This builds the scene for Figure 24.17
#include "../tracers/Whitted.hpp"
#include "../tracers/Whitted.hpp"
#include "../cameras/Pinhole.hpp"
#include "../lights/PointLight.hpp"
#include "../lights/AmbientLight.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"
#include "../samplers/MultiJittered.hpp"
#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Rectangle.hpp"

void 												
World::build(void) {
	int num_samples = 16;
	
	vplane.set_hres(600);	  		
	vplane.set_vres(600);
	vplane.top_left = Point3D(0, 10, 14.14);
	vplane.bottom_right = Point3D(14.14, -10, 0);

	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->set_num_sets(vplane.hres*vplane.vres);
	sampler_ptr->generate_samples();
	sampler_ptr->map_samples_to_hemisphere(10);
	// vplane.set_samples(num_samples);
	// vplane.max_depth = 0;	//  for Figure 24.17(a)
	// vp.set_max_depth(1);	//  for Figure 24.17(b)
	vplane.max_depth = 2;	//  for Figure 24.17(c)
	
	tracer_ptr = new Whitted(this);
			
	Pinhole* pinhole_ptr = new Pinhole(Point3D(12, 0, 12), Point3D(0, 0, 0), 300.0);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	grid_ptr = new Acceleration();

	ambient_ptr = new AmbientLight(0.2, black + 0.1);
	
	// four point lights near the ceiling
	// these don't use distance attenuation

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(10, 10, 0); 
	light_ptr1->scale_radiance(2.0); 
	// light_ptr1->set_shadows(true); 
    add_light(light_ptr1);
    
    PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(0, 10, 10); 
	light_ptr2->scale_radiance(2.0); 
	// light_ptr2->set_shadows(true); 
    add_light(light_ptr2);
    
    PointLight* light_ptr3 = new PointLight;
	light_ptr3->set_location(-10, 10, 0); 
	light_ptr3->scale_radiance(2.0); 
	// light_ptr3->set_shadows(true); 
    add_light(light_ptr3);
    
    PointLight* light_ptr4 = new PointLight;
	light_ptr4->set_location(0, 10, -10); 
	light_ptr4->scale_radiance(2.0); 
	// light_ptr4->set_shadows(true); 
    add_light(light_ptr4);

		
	// sphere
	// this is the only reflective object with a direct illumination shading component
	
	Reflective* reflective_ptr1 = new Reflective;			
	reflective_ptr1->set_ka(0.1); 
	reflective_ptr1->set_kd(0.4); 
	reflective_ptr1->set_cd(RGBColor(0, 0, 1));   	 // blue
	reflective_ptr1->set_ks(0.25);
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.85); 
	reflective_ptr1->set_cr(RGBColor(0.75, 0.75, 1.0));  // blue 
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0, 0.5, 0), 4); 
	sphere_ptr1->set_material(reflective_ptr1);
	grid_ptr->add_object(sphere_ptr1);
		
	
	// the walls, the ceiling, and the floor of the room are defined as planes
	// the shape is a cube
	
	double room_size = 11.0;
	
	// floor  (-ve yw)
	
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.1);
	matte_ptr1->set_kd(0.50);
	matte_ptr1->set_cd(0.25);     // medium grey
	
	Plane* floor_ptr = new Plane(Point3D(0, -room_size,  0), Vector3D(0, 1, 0));
	floor_ptr->set_material(matte_ptr1);        
	add_geometry(floor_ptr);
	
	
	// ceiling  (+ve yw)
	
	Matte* matte_ptr2 = new Matte;   
	matte_ptr2->set_ka(0.35);   
	matte_ptr2->set_kd(0.50);
	matte_ptr2->set_cd(white);
	
	Plane* ceiling_ptr = new Plane(Point3D(0, room_size,  0), Vector3D(0, -1, 0));
	ceiling_ptr->set_material(matte_ptr2);        
	add_geometry(ceiling_ptr);
	
	
	// back wall  (-ve zw)
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15); 
	matte_ptr3->set_kd(0.60);
	matte_ptr3->set_cd(RGBColor(0.5, 0.75, 0.75));     // cyan
	
	Plane* backWall_ptr = new Plane(Point3D(0, 0,  -room_size), Vector3D(0, 0, 1));
	backWall_ptr->set_material(matte_ptr3);        
	add_geometry(backWall_ptr);
	
	// front wall  (+ve zw)
	
	Plane* frontWall_ptr = new Plane(Point3D(0, 0,  room_size), Vector3D(0, 0, -1));
	frontWall_ptr->set_material(matte_ptr3);        
	add_geometry(frontWall_ptr);
	
	// left wall  (-ve xw)
	
	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(0.15); 
	matte_ptr4->set_kd(0.60);
	matte_ptr4->set_cd(RGBColor(0.71, 0.40, 0.20));   // orange
	
	Plane* leftWall_ptr = new Plane(Point3D(-room_size, 0, 0), Vector3D(1, 0, 0));
	leftWall_ptr->set_material(matte_ptr4);        
	add_geometry(leftWall_ptr);
	
	// right wall  (+ve xw)
	
	Plane* rightWall_ptr = new Plane(Point3D(room_size, 0, 0), Vector3D(-1, 0, 0));
	rightWall_ptr->set_material(matte_ptr4);        
	add_geometry(rightWall_ptr);
	
	
	// mirrors on the walls
	// the right wall has no mirror
	
	double mirror_size 	= 8;  	// the mirror size
	double offset 		= 1.0;  // the mirror offset from the walls
	
	// mirror material
	// this has no direct illumination and a slight green tint
	
	Reflective* reflective_ptr2 = new Reflective;			
	reflective_ptr2->set_ka(0); 
	reflective_ptr2->set_kd(0);
	reflective_ptr2->set_cd(black); 
	reflective_ptr2->set_ks(0);
	reflective_ptr2->set_kr(0.9);
	reflective_ptr2->set_cr(RGBColor(0.9, 1.0, 0.9));  // light green
	
	// back wall mirror  (-ve zw)

	Point3D p0;
	Vector3D a, b;
	
	p0 = Point3D(-mirror_size, -mirror_size, -(room_size - offset));
	a = Vector3D(2.0 * mirror_size, 0, 0);
	b = Vector3D(0, 2.0 * mirror_size, 0);
	Vector3D n(0, 0, 1);
	Rectangle* rectangle_ptr1 = new Rectangle(p0, a, b, n);
	rectangle_ptr1->set_material(reflective_ptr2); 
	grid_ptr->add_object(rectangle_ptr1);
	
	
	// front wall mirror  (+ve zw)
	
	p0 = Point3D(-mirror_size, -mirror_size, +(room_size - offset));
	n = Vector3D(0, 0, -1);
	Rectangle* rectangle_ptr2 = new Rectangle(p0, a, b, n);
	rectangle_ptr2->set_material(reflective_ptr2); 
	grid_ptr->add_object(rectangle_ptr2);
	
	
	// left wall mirror  (-ve xw)
	
	p0 = Point3D(-(room_size - offset), -mirror_size, +mirror_size);
	a = Vector3D(0, 0, -2.0 * mirror_size);
	n = Vector3D(1, 0, 0);
	Rectangle* rectangle_ptr3 = new Rectangle(p0, a, b, n);
	rectangle_ptr3->set_material(reflective_ptr2); 
	grid_ptr->add_object(rectangle_ptr3);


	// horizontal mirror underneath the sphere
	// this has no direct illumination and a lemon color
	
	Reflective* reflective_ptr3 = new Reflective;			
	reflective_ptr3->set_ka(0); 
	reflective_ptr3->set_kd(0);
	reflective_ptr3->set_cd(black); 
	reflective_ptr3->set_ks(0);
	reflective_ptr3->set_kr(1);
	reflective_ptr3->set_cr(RGBColor(1, 1, 0.5));  // lemon
	
	double yw = -4.0;   // the yw location of the mirror
	
	p0 = Point3D(-mirror_size, yw, -mirror_size);
	a = Vector3D(0, 0, 2.0 * mirror_size);
	b = Vector3D(2.0 * mirror_size, 0, 0);
	n = Vector3D(0, 1, 0);
	Rectangle* rectangle_ptr4 = new Rectangle(p0, a, b, n);
	rectangle_ptr4->set_material(reflective_ptr3); 
	grid_ptr->add_object(rectangle_ptr4);
	grid_ptr->setup_cells();
	add_geometry(grid_ptr);
}



