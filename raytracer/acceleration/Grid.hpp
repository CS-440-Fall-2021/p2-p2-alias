#include "../raytracer/utilities/Point3D.hpp"
#include "../raytracer/utilities/Vector3D.hpp"
#include "../raytracer/utilities/BBox.hpp"
#include "../raytracer/utilities/Ray.hpp"
#include "../raytracer/utilities/Constants.hpp"
#include <vector> 
#include "../raytracer/geometry/Compound.hpp"
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