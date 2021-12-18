// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <vector> 
#include "Compound.hpp"
using namespace std;

					

// ----------------------------------------------------------------  default constructor

Compound::Compound (void)
	: 	Geometry()
{}


// ---------------------------------------------------------------- clone

Compound* 
Compound::clone(void) const {
	return (new Compound(*this));
}

std::string Compound::to_string() const
{
    std::string s;
    return s;
}
// ---------------------------------------------------------------- copy constructor

Compound::Compound (const Compound& c)
	: Geometry(c) {
	
	copy_objects(c.objects);					
}



// ---------------------------------------------------------------- assignment operator

Compound& 
Compound::operator= (const Compound& rhs) {
	if (this == &rhs)
		return (*this);

	Geometry::operator= (rhs);						
	
	copy_objects(rhs.objects);				

	return (*this);
}


// ---------------------------------------------------------------- destructor

Compound::~Compound(void) {	
	delete_objects();				
}


// ---------------------------------------------------------------- add_object

void 
Compound::add_object(Geometry* object_ptr) {
	objects.push_back(object_ptr);	
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
Compound::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
Compound::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

// void
// Compound::copy_objects(const vector<Geometry*>& rhs_ojects) {
// 	delete_objects();    	
// 	int num_objects = rhs_ojects.size();
	
// 	for (int j = 0; j < num_objects; j++)
// 		objects.push_back(rhs_ojects[j]->clone());
// }


//------------------------------------------------------------------ hit

bool 															 
Compound::hit(const Ray& ray, float& tmin, ShadeInfo & sr) const {
	float	t; 
	Vector3D normal;
	Point3D	local_hit_point;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			hit				= true;
			tmin 			= t;
			Material* material_ptr	= objects[j]->get_material();	// lhs is GeometricObject::material_ptr
			normal			= sr.normal;
			local_hit_point	= sr.hit_point;  
		}
	
	if (hit) {
		sr.t				= tmin;
		sr.normal 			= normal;   
		sr.hit_point 	= local_hit_point;  
	}
	
	return (hit);
}

BBox Compound::getBBox() const {
    
};
