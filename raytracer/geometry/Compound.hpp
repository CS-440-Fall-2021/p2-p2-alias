#pragma once
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector> 
#include "Geometry.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/BBox.hpp"
using namespace std;
//-------------------------------------------------------------------------------- class Compound

class Compound: public Geometry {	
	public:
		
		Compound(void);   										

		virtual Compound* 										
		clone(void) const;
	
		Compound(const Compound& c); 							

		~Compound (void);   									

		Compound& 												
		operator= (const Compound& c);	
		
		virtual void 
		set_material(Material* material_ptr);
		
		virtual void 											
		add_object(Geometry* object_ptr);  

        std::string to_string() const override;
		
		int
		get_num_objects(void);						

		virtual bool hit(const Ray& ray, float& tmin, ShadeInfo& s) const;
 
		virtual BBox getBBox() const override;
	protected:		
		
		vector<Geometry*> objects;
		
	private:
	
		void 													
		delete_objects(void);								

		void												
		copy_objects(const vector<Geometry*>& rhs_objects);
	
};


// ------------------------------------------------------------------------------- get_num_objects

inline int
Compound::get_num_objects(void) {
	return (objects.size());
}
