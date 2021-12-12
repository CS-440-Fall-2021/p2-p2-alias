#include "BBox.hpp"

BBox::BBox(const Point3D& min, const Point3D& max){

}

std::string BBox::to_string() const{

}
bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const{

}

void BBox::extend(Geometry* g){

}

void BBox::extend(const BBox& b){

}

bool BBox::contains(const Point3D& p){

}

bool BBox::overlaps(Geometry* g){

}

bool BBox::overlaps(const BBox& b){

}