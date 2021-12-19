#pragma once 

#include "Tracer.hpp"

class Whitted : public Tracer{
    Whitted();
		
    Whitted(World* _worldPtr);
    
    ~Whitted();

    RGBColor trace_ray(const Ray ray, const int depth) ;

};