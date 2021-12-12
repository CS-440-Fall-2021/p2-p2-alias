#include "Simple.hpp"

Simple::Simple(Camera *c_ptr, ViewPlane *v_ptr){
    camera_ptr=c_ptr;
    viewplane_ptr=v_ptr;
}

Simple::Simple(const Simple &camera){
    camera_ptr=camera.camera_ptr;
    viewplane_ptr=camera.viewplane_ptr;
}

Simple &Simple::operator=(const Simple &other){
    camera_ptr=other.camera_ptr;
    viewplane_ptr=other.viewplane_ptr;
    return *this;
}

std::vector<Ray> Simple::get_rays(int px, int py) const{ 
    // computing hres and vres of one pixel
    float h = (viewplane_ptr->bottom_right.x - viewplane_ptr->top_left.x) / viewplane_ptr->hres;
    float v = (viewplane_ptr->top_left.y - viewplane_ptr->bottom_right.y) / viewplane_ptr->vres;
    
    // computing the position of the ray
    float xpos = viewplane_ptr->top_left.x + h * (px + 0.5);
    float ypos = viewplane_ptr->top_left.y - v * (py + 0.5);
    
    Point3D point = Point3D(xpos, ypos, viewplane_ptr->bottom_right.z);
    Vector3D dir = camera_ptr->get_direction(point);
    
    dir.normalize();
    std::vector<Ray> rays {Ray(point, dir)};
    return rays;
    
}
