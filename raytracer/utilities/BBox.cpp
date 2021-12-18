#include "BBox.hpp"



#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

BBox::BBox(const Point3D& min, const Point3D& max){
  pmin = min;
  pmax = max;
}

std::string BBox::to_string() const{
  return ("BBox min point: " + pmin.to_string() + ", max point: " + pmax.to_string());
}

bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const{

  float tx_enter = (pmin.x - ray.o.x)/ ray.d.x ;
  float tx_leave = (pmax.x - ray.o.x)/ ray.d.x ;

  float ty_enter = (pmin.y - ray.o.y)/ ray.d.y ;
  float ty_leave = (pmax.y - ray.o.y)/ ray.d.y ;

  float tz_enter = (pmin.z - ray.o.z)/ ray.d.z ;
  float tz_leave = (pmax.z - ray.o.z)/ ray.d.z ;

  // Find the largest entering t value 
  float tmax_enter = MAX(tx_enter,MAX(ty_enter,tz_enter));
  // Find the smallest leaving t value 
  float tmin_leave = MIN(tx_leave,MIN(ty_leave,tz_leave));

  // If largest entering t < Smallest leaving t, hit has occured
  if (tmax_enter < tmin_leave){
    return true;
  }
  else{
    return false;
  }

}

void BBox::extend(Geometry* g){
  extend(g->getBBox());
}

void BBox::extend(const BBox& b){
  pmin = min(b.pmin,pmin);
  pmax = max(b.pmax,pmax);
}

bool BBox::contains(const Point3D& p) const{
    if (pmin.x <= p.x && p.x <= pmax.x &&
        pmin.y <= p.y && p.y <= pmax.y &&
        pmin.z <= p.z && p.z <= pmax.z)
    {
        return true;
    }
    else {
        return false;
    }
}

bool BBox::overlaps(Geometry* g){
    return this->overlaps(g->getBBox());
}

bool BBox::overlaps(const BBox& b){

    // Check overlap in x slap
    // If calling BBox is ahead along x-axis of b BBox
    if (pmax.x >= b.pmax.x){
        // If calling BBox's back along x-axis is behind of b BBox's front along x-axis
        if (pmin.x > b.pmax.x){
            return false;
        }
    }
    // If b BBox is behind along x-axis of calling BBox  
    else {
        // If b BBox's back along x-axis is behind of calling BBox's front along x-axis
        if (b.pmax.x > pmin.x){
            return false;
        }
    }

    // Check overlap in y slap
    // If calling BBox is ahead along y-axis of b BBox
    if (pmax.y >= b.pmax.y){
        // If calling BBox's back along y-axis is behind of b BBox's front along y-axis
        if (pmin.y > b.pmax.y){
            return false;
        }
    }
    // If b BBox is behind along y-axis of calling BBox  
    else {
        // If b BBox's back along y-axis is behind of calling BBox's front along y-axis
        if (b.pmax.y > pmin.y){
            return false;
        }
    }

    // Check overlap in z slab
    // If calling BBox is ahead along z-axis of b BBox
    if (pmax.z >= b.pmax.z){
        // If calling BBox's back along x-axis is behind of b BBox's front along x-axis
        if (pmin.z > b.pmax.z){
            return false;
        }
    }
    // If b BBox is behind along x-axis of calling BBox  
    else {
        // If b BBox's back along x-axis is behind of calling BBox's front along x-axis
        if (b.pmax.z > pmin.z){
            return false;
        }
    }

    // As overlap is along all axis the bounding boxes overlap
    return true;
}