#pragma once

#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include <vector> 
#include "../geometry/Compound.hpp"
using namespace std;

class Acceleration : public Compound
{
public:
    Acceleration(void);
    // other constructors, etc.
    virtual BBox
    get_bounding_box(void);
    void
    setup_cells(void);
    virtual bool hit(Ray &ray, float &tmin, ShadeInfo &s);
    virtual bool
    shadow_hit(Ray &ray, float &tmin);

private:
    vector<Compound*> cells; // cells are stored in a 1D array
    BBox bbox;                       // bounding box
    int nx, ny, nz;                  // number of cells in the x-, y-, and z-directions
    Point3D                          // compute minimum grid coordinates
    min_coordinates(void);
    Point3D // compute maximum grid coordinates
    max_coordinates(void);
};