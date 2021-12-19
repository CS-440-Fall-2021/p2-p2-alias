
/**
   This builds a scene that consists of 35 shaded spheres and a plane.
   Perspective viewing is used with a single sample per pixel.
   The spheres are the same as those in the Chapter 14 page one image. 

   Courtesy Kevin Suffern.
*/

#include "../acceleration/Acceleration.hpp"

#include "../cameras/Parallel.hpp"
#include "../cameras/Pinhole.hpp"

#include "../lights/AmbientLight.hpp"
#include "../lights/PointLight.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"

#include "../tracers/Basic.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"

#include <iostream>

void
World::build(void) {
  // view plane  
  vplane.top_left.x = -200;
  vplane.top_left.y = 200;
  vplane.top_left.z = 100;
  vplane.bottom_right.x = 200;
  vplane.bottom_right.y = -200;
  vplane.bottom_right.z = 100;
  vplane.hres = 400;
  vplane.vres = 400;

  tracer_ptr = new Basic(this);
  Acceleration* grid_ptr = new Acceleration(50,50,50);
  
  bg_color = black;  // background color.
  
  // camera and sampler.
  Camera *cam = new Pinhole(Point3D(0, 0, 400), Point3D(0, 0, -300), 300);
  cam->compute_uvw();
  set_camera(cam);
  sampler_ptr = new Simple(camera_ptr, &vplane);
	
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
  RGBColor grey(0.25);  // grey
  RGBColor white(1);  // grey

  ambient_ptr = new AmbientLight(0.1, white);
  Light *point_light1 = new PointLight(1, white, Vector3D(-40, 100, 50));
	add_light(point_light1);

  Lambertian *ambient_brdf = new Lambertian(0.9, white);
  // spheres
  Sphere* sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
  sphere_ptr1->set_material(new Matte(ambient_brdf,  new Lambertian(1, yellow)));  // yellow
  // add_geometry(sphere_ptr1);
  grid_ptr->add_object(sphere_ptr1);
	
  Sphere* sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
  sphere_ptr2->set_material(new Matte(ambient_brdf,  new Lambertian(1, brown)));  // brown
  // add_geometry(sphere_ptr2);
  grid_ptr->add_object(sphere_ptr2);

  Sphere* sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
  sphere_ptr3->set_material(new Matte(ambient_brdf,  new Lambertian(1, darkGreen)));  // dark green
  // add_geometry(sphere_ptr3);
  grid_ptr->add_object(sphere_ptr3);
	
  Sphere* sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
  sphere_ptr4->set_material(new Matte(ambient_brdf,  new Lambertian(1, orange)));  // orange
  // add_geometry(sphere_ptr4);
  grid_ptr->add_object(sphere_ptr4);
	
  Sphere* sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27); 			
  sphere_ptr5->set_material(new Matte(ambient_brdf,  new Lambertian(1, green)));  // green
  // add_geometry(sphere_ptr5);
  grid_ptr->add_object(sphere_ptr5);
	
  Sphere* sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
  sphere_ptr6->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightGreen)));  // light green
  // add_geometry(sphere_ptr6);
  grid_ptr->add_object(sphere_ptr6);
	
  Sphere* sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
  sphere_ptr7->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, green)));  // green
  // add_geometry(sphere_ptr7);
  grid_ptr->add_object(sphere_ptr7);
	
  Sphere* sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
  sphere_ptr8->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, brown)));  // brown
  // add_geometry(sphere_ptr8);
  grid_ptr->add_object(sphere_ptr8);
	
  Sphere* sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
  sphere_ptr9->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightGreen)));  // light green
  // add_geometry(sphere_ptr9);
  grid_ptr->add_object(sphere_ptr9);
		
  Sphere* sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
  sphere_ptr10->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkGreen)));  // dark green
  // add_geometry(sphere_ptr10);
  grid_ptr->add_object(sphere_ptr10);
	
  Sphere* sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
  sphere_ptr11->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkYellow)));  // dark yellow
  // add_geometry(sphere_ptr11);
  grid_ptr->add_object(sphere_ptr11);
	
  Sphere* sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
  sphere_ptr12->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkYellow)));  // dark yellow
  // add_geometry(sphere_ptr12);
  grid_ptr->add_object(sphere_ptr12);
	
  Sphere* sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
  sphere_ptr13->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkYellow)));  // dark yellow (hidden)
  // add_geometry(sphere_ptr13);
  grid_ptr->add_object(sphere_ptr13);
  
  Sphere* sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
  sphere_ptr14->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkGreen)));  // dark green
  // add_geometry(sphere_ptr14);
  grid_ptr->add_object(sphere_ptr14);
	
  Sphere* sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
  sphere_ptr15->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, brown)));  // brown
  // add_geometry(sphere_ptr15);
  grid_ptr->add_object(sphere_ptr15);
	
  Sphere* sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
  sphere_ptr16->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightPurple)));  // light purple
  // add_geometry(sphere_ptr16);
  grid_ptr->add_object(sphere_ptr16);
	
  Sphere* sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15); 		
  sphere_ptr17->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, brown)));  // browm
  // add_geometry(sphere_ptr17);
  grid_ptr->add_object(sphere_ptr17);
	
  Sphere* sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
  sphere_ptr18->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkPurple)));  // dark purple
  // add_geometry(sphere_ptr18);
  grid_ptr->add_object(sphere_ptr18);
	
  Sphere* sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
  sphere_ptr19->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkGreen)));  // dark green
  // add_geometry(sphere_ptr19);
  grid_ptr->add_object(sphere_ptr19);

  Sphere* sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
  sphere_ptr20->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, brown)));  // browm
  // add_geometry(sphere_ptr20);
  grid_ptr->add_object(sphere_ptr20);
	 
  Sphere* sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
  sphere_ptr21->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightPurple)));  // light purple
  // add_geometry(sphere_ptr21);
  grid_ptr->add_object(sphere_ptr21);
	
  Sphere* sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
  sphere_ptr22->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightPurple)));  // light purple
  // add_geometry(sphere_ptr22);
  grid_ptr->add_object(sphere_ptr22);
	
  Sphere* sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13);
  sphere_ptr23->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkPurple)));  // dark purple
  // add_geometry(sphere_ptr23);	
  grid_ptr->add_object(sphere_ptr23);
	
  Sphere* sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12); 
  sphere_ptr24->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightPurple)));  // light purple
  // add_geometry(sphere_ptr24);
  grid_ptr->add_object(sphere_ptr24);
	
  Sphere* sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11); 			
  sphere_ptr25->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, green)));  // green
  // add_geometry(sphere_ptr25);
  grid_ptr->add_object(sphere_ptr25);
	  
  Sphere* sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12); 		
  sphere_ptr26->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightPurple)));  // light purple
  // add_geometry(sphere_ptr26);
  grid_ptr->add_object(sphere_ptr26);
	
  Sphere* sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12); 		
  sphere_ptr27->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, lightPurple)));  // light purple
  // add_geometry(sphere_ptr27);
  grid_ptr->add_object(sphere_ptr27);
	 
  Sphere* sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
  sphere_ptr28->set_material(new Matte(ambient_brdf,  new Lambertian(0.8, darkPurple)));  // dark purple
  // add_geometry(sphere_ptr28);
  grid_ptr->add_object(sphere_ptr28);
	
  Sphere* sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
  sphere_ptr29->set_material(new Cosine(darkPurple));  // dark purple
  // add_geometry(sphere_ptr29);
  grid_ptr->add_object(sphere_ptr29);
	
  Sphere* sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
  sphere_ptr30->set_material(new Cosine(darkPurple));  // dark purple
  // add_geometry(sphere_ptr30);
  grid_ptr->add_object(sphere_ptr30);
	
  Sphere* sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
  sphere_ptr31->set_material(new Cosine(lightPurple));  // light purple
  // add_geometry(sphere_ptr31);
  grid_ptr->add_object(sphere_ptr31);
	
  Sphere* sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
  sphere_ptr32->set_material(new Cosine(green));  //  green
  // add_geometry(sphere_ptr32);
  grid_ptr->add_object(sphere_ptr32);
	
  Sphere* sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
  sphere_ptr33->set_material(new Cosine(green));  // green 
  // add_geometry(sphere_ptr33);
  grid_ptr->add_object(sphere_ptr33);
	
  Sphere* sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10); 	
  sphere_ptr34->set_material(new Cosine(lightPurple));  // light purple
  // add_geometry(sphere_ptr34);
  grid_ptr->add_object(sphere_ptr34);
	
  Sphere* sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
  sphere_ptr35->set_material(new Cosine(lightPurple));  // light purple
  // add_geometry(sphere_ptr35);
  grid_ptr->add_object(sphere_ptr35);
	
  // vertical plane
  Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Vector3D(0, 0, 1));
  plane_ptr->set_material(new Cosine(grey));
  add_geometry(plane_ptr);
  // grid_ptr->add_object(plane_ptr);

  grid_ptr->setup_cells();
  add_geometry(grid_ptr);
}

