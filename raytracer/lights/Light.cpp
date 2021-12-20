#include "Light.hpp"

void Light::set_shadows(const bool _shadows){
    shadows = _shadows;
}

bool Light::get_shadows() const{
    return shadows;
}