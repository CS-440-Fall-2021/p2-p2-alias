#include "Geometry.hpp"

Geometry::Geometry(){
    material_ptr = NULL;
}

Material *Geometry::get_material() const{
    return material_ptr;
}

void Geometry::set_material(Material *mPtr){
    material_ptr = mPtr;
}