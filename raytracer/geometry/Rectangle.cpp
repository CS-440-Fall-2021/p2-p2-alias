#include "Rectangle.hpp"

Rectangle::Rectangle()
{
    p0 = Point3D();
    a = Vector3D();
    b = Vector3D();
    normal = a ^ b;
    normal.normalize();
    a_len_squared = a.len_squared();
    b_len_squared = b.len_squared();
}

Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b)
{
    p0 = _p0;
    a = _a;
    b = _b;
    normal = a ^ b;
    normal.normalize();
    a_len_squared = a.len_squared();
    b_len_squared = b.len_squared();
}

std::string Rectangle::to_string() const
{
    std::string out = "a: " + a.to_string() + "\n" +
                      "b: " + b.to_string() + "\n" +
                      "p0: " + p0.to_string() + "\n";
    return out;
}

bool Rectangle::hit(const Ray& ray, double& t, ShadeInfo& s) const {	
	
	double ti = (p0 - ray.o) * normal / (ray.d * normal); 
	
	if (ti <= kEpsilon)
		return (false);
			
	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;
	
	double ddota = d * a;
	
	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);
		
	double ddotb = d * b;
	
	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);
		
    t = ti;
    s.normal=normal;
    s.normal.normalize();
    s.hit_point= ray.o + ti * ray.d;
    s.hit = true;
    s.material_ptr = material_ptr;
    s.ray = ray;
    s.t = ti;

    return true;
	

}

BBox Rectangle::getBBox() const{
    Point3D P1 = p0;
    Point3D P2 = p0 + a;
    Point3D P3 = p0 + b;
    Point3D P4 = p0 + a + b;

    Point3D PMIN = min(min(P1,P2),min(P3,P4));
    Point3D PMAX = max(max(P1,P2),max(P3,P4));
    return BBox(PMIN, PMAX);
}

Rectangle *Rectangle::clone() const{
	return (new Rectangle(*this));
}