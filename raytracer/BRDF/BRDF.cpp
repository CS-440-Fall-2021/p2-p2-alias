#include "BRDF.hpp"

BRDF::BRDF(): 
    sampler_ptr(NULL), 
    normal()
{}

BRDF::BRDF(Sampler *sampler_ptr_, Vector3D normal_){
    sampler_ptr = sampler_ptr_;
    normal = normal_;
}
