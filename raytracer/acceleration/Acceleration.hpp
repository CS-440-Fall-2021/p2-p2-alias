#pragma once

#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include <vector> 
#include "../geometry/Compound.hpp"

class Acceleration : public Compound
{
public:
    Acceleration();
    Acceleration(int nx_, int ny_, int nz_);

    Acceleration(Acceleration &) = default;
    Acceleration &operator=(Acceleration &) = default;

    ~Acceleration() = default;
    // other constructors, etc.
    // BBox
    // getBBox(void);
    void
    setup_cells(void);
    virtual bool hit(const Ray &ray, float &tmin, ShadeInfo &s) const;
    virtual bool
    shadow_hit(Ray &ray, float &tmin);

private:
    std::vector<Geometry*> cells; // cells are stored in a 1D array
    BBox bbox;                       // bounding box
    int nx, ny, nz;                  // number of cells in the x-, y-, and z-directions
    Point3D                          // compute minimum grid coordinates
    min_coordinates(void);
    Point3D // compute maximum grid coordinates
    max_coordinates(void);
};