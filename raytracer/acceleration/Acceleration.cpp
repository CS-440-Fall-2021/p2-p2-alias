#include "Acceleration.hpp"
#include <math.h>

Acceleration::Acceleration(){
    Compound();

}

Point3D Acceleration::min_coordinates(void)
{
    BBox bbox;
    Point3D p0(kHugeValue);
    int num_objects = objects.size();
    for (int j = 0; j < num_objects; j++)
    {
        bbox = objects[j]->getBBox();
        if (bbox.pmin.x < p0.x)
            p0.x = bbox.pmin.x;
        if (bbox.pmin.y < p0.y)
            p0.y = bbox.pmin.y;
        if (bbox.pmin.z < p0.z)
            p0.z = bbox.pmin.z;
    }
    p0.x -= kEpsilon;
    p0.y -= kEpsilon;
    p0.z -= kEpsilon;
    return (p0);
}


Point3D Acceleration::max_coordinates(void)
{
    BBox bbox;
    Point3D p0(kEpsilon);
    int num_objects = objects.size();
    for (int j = 0; j < num_objects; j++)
    {
        bbox = objects[j]->getBBox();
        if (bbox.pmax.x > p0.x)
            p0.x = bbox.pmax.x;
        if (bbox.pmax.y > p0.y)
            p0.y = bbox.pmax.y;
        if (bbox.pmax.z > p0.z)
            p0.z = bbox.pmax.z;
    }
    p0.x += kEpsilon;
    p0.y += kEpsilon;
    p0.z += kEpsilon;
    return (p0);
}

inline float
clamp(float x, float min, float max)
{
    return (x < min ? min : (x > max ? max : x));
}

void Acceleration::setup_cells(void)
{
    // find the minimum and maximum coordinates of the grid
    Point3D p0 = min_coordinates();
    Point3D p1 = max_coordinates();
    // store them in the bounding box
    bbox.pmin.x = p0.x;
    bbox.pmin.y = p0.y;
    bbox.pmin.z = p0.z;
    bbox.pmax.x = p1.x;
    bbox.pmax.y = p1.y;
    bbox.pmax.z = p1.z;
    // compute the number of cells in the x-, y-, and z-directions
    int num_objects = objects.size();
    float wx = p1.x - p0.x; // grid extent in x-direction
    float wy = p1.y - p0.y; // grid extent in y-direction
    float wz = p1.z - p0.z; // grid extent in z-direction
    float multiplier = 2.0; // about 8 times more cells than objects
    float s = pow(wx * wy * wz / num_objects, 0.3333333);
    nx = multiplier * wx / s + 1;
    ny = multiplier * wy / s + 1;
    nz = multiplier * wz / s + 1;
    // set up the array of cells with null pointers
    int num_cells = nx * ny * nz;
    cells.reserve(num_objects);
    for (int j = 0; j < num_cells; j++)
        cells.push_back(NULL);
    // set up a temporary array to hold the number of objects stored in each cell
    std::vector<int> counts;
    counts.reserve(num_cells);
    for (int j = 0; j < num_cells; j++)
        counts.push_back(0);
    // put objects into the cells
    BBox obj_bbox; // object’s bounding box
    int index;     // cells array index
    for (int j = 0; j < num_objects; j++)
    {
        obj_bbox = objects[j]->getBBox();
        // compute the cell indices for the corners of the bounding box of the
        // object
        int ixmin = clamp((obj_bbox.pmin.x - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
        int iymin = clamp((obj_bbox.pmin.y - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
        int izmin = clamp((obj_bbox.pmin.z - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
        int ixmax = clamp((obj_bbox.pmax.x - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
        int iymax = clamp((obj_bbox.pmax.y - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
        int izmax = clamp((obj_bbox.pmax.z - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
        // add the object to the cells
        for (int iz = izmin; iz <= izmax; iz++)
        { // cells in z direction
            for (int iy = iymin; iy <= iymax; iy++)
            { // cells in y direction
                for (int ix = ixmin; ix <= ixmax; ix++)
                { // cells in x
                    // direction
                    index = ix + nx * iy + nx * ny * iz;
                    if (counts[index] == 0)
                    {
                        cells[index] = objects[j];
                        counts[index] += 1;
                        index = 1;
                    }
                    else
                    {
                        if (counts[index] == 1)
                        {
                            // construct a compound object
                            Compound *compound_ptr = new Compound;
                            // add the object already in cell
                            compound_ptr->add_object(cells[index]);
                            // add the new object
                            compound_ptr->add_object(objects[j]);
                            // store compound in current cell
                            cells[index] = compound_ptr;
                            // index = 2
                            counts[index] += 1;
                        }
                        else
                        { // counts[index] > 1
                            // just add current object
                            cells[index]->add_object(objects[j]);
                            // for statistics only
                            counts[index] += 1;
                        }
                    }
                }
            }
        }

    }
    // erase Compound::Objects, but don’t delete the objects
objects.erase (objects.begin(), objects.end());
// code for statistics on cell objects counts can go in here
// erase the temporary counts vector
counts.erase (counts.begin(), counts.end());
}



bool Acceleration::hit(const Ray& ray, float& tmin, ShadeInfo& s) const{

    int ix, iy, iz;
    float x0 = bbox.pmin.x;
    float y0 = bbox.pmin.y;
    float z0 = bbox.pmin.z;
    float x1 = bbox.pmax.x;
    float y1 = bbox.pmax.y;
    float z1 = bbox.pmax.z;

    float ox = ray.o.x;
    float oy = ray.o.y;
    float oz = ray.o.z;

    float t0, t1 = 0;

    if (! bbox.hit(ray, t0, t1))
        return false;

    if (bbox.contains(ray.o)) {
        ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
        iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
        iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
    }
    else {
    Point3D p = ray.o + t0 * ray.d;
        ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
        iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
        iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
    }

    float tx_min = (x0 - ox) / ray.d.x;
    float tx_max = (x1 - ox) / ray.d.x;
    float ty_min = (y0 - oy) / ray.d.y;
    float ty_max = (y1 - oy) / ray.d.y;
    float tz_min = (z0 - oz) / ray.d.z;
    float tz_max = (z1 - oz) / ray.d.z;

    float dtx = (tx_max - tx_min) / nx;
    float dty = (ty_max - ty_min) / ny;
    float dtz = (tz_max - tz_min) / nz;
    
    float tx_next, ty_next, tz_next;
    
    int ix_step, iy_step, iz_step;
    int ix_stop, iy_stop, iz_stop;

    tx_next = tx_min + (ix + 1) * dtx;
    ix_step = +1;
    ix_stop = nx;
    
    ty_next = ty_min + (iy + 1) * dty;
    iy_step = +1;
    iy_stop = ny;
    
    tz_next = tz_min + (iz + 1) * dtz;
    iz_step = +1;
    iz_stop = nz;

    while (true) {
        Geometry* object_ptr = cells[ix + nx * iy + nx * ny * iz];
        if (tx_next < ty_next && tx_next < tz_next) {
            if (object_ptr && object_ptr->hit(ray, tmin, s) && tmin < tx_next) {
            material_ptr = object_ptr->get_material();
            return (true);
            }
            tx_next += dtx;
            ix += ix_step;
            if (ix == ix_stop)
                return (false);
        }
        else {
            if (ty_next < tz_next) {
                if (object_ptr && object_ptr->hit(ray, tmin, s) && tmin < ty_next) {
                    material_ptr = object_ptr->get_material();
                    return (true);
                }
                ty_next += dty;
                iy += iy_step;
                if (iy == iy_stop)
                    return (false);
            }
            else {
                if (object_ptr && object_ptr->hit(ray, tmin, s) && tmin < tz_next) {
                    material_ptr = object_ptr->get_material();
                    return (true);
                }
                tz_next += dtz;
                iz += iz_step;

                if (iz == iz_stop)
                    return (false);
            }
        }
    }
}

bool Acceleration::shadow_hit(Ray &ray, float &tmin){return false;}