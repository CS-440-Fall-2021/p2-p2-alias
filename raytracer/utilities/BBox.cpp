#include "BBox.hpp"
#include "../utilities/Constants.hpp"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

BBox::BBox(const Point3D &min, const Point3D &max)
{
    pmin = min;
    pmax = max;
}

std::string BBox::to_string() const
{
    return ("BBox min point: " + pmin.to_string() + ", max point: " + pmax.to_string());
}

bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const
{

    float ox = ray.o.x;
    float oy = ray.o.y;
    float oz = ray.o.z;
    float dx = ray.d.x;
    float dy = ray.d.y;
    float dz = ray.d.z;
    float tx_min, ty_min, tz_min;
    float tx_max, ty_max, tz_max;
    float a = 1.0 / dx;

    if (a >= 0)
    {
        tx_min = (pmin.x - ox) * a;
        tx_max = (pmax.x - ox) * a;
    }
    else
    {
        tx_min = (pmax.x - ox) * a;
        tx_max = (pmin.x - ox) * a;
    }
    if (dx == 0.0){
        tx_min = kEpsilon;
        tx_max = kHugeValue;
    }
    float b = 1.0 / dy;
    if (b >= 0)
    {
        ty_min = (pmin.y - oy) * b;
        ty_max = (pmax.y - oy) * b;
    }
    else
    {
        ty_min = (pmax.y - oy) * b;
        ty_max = (pmin.y - oy) * b;
    }
    if (dy == 0.0){
        ty_min = kEpsilon;
        ty_max = kHugeValue;
    }
    
    float c = 1.0 / dz;
    if (c >= 0)
    {
        tz_min = (pmin.z - oz) * c;
        tz_max = (pmax.z - oz) * c;
    }
    else
    {
        tz_min = (pmax.z - oz) * c;
        tz_max = (pmin.z - oz) * c;
    }
    if (dz == 0.0){
        tz_min = kEpsilon;
        tz_max = kHugeValue;
    }

    // find largest entering t value
    if (tx_min > ty_min)
        t_enter = tx_min;
    else
        t_enter = ty_min;
    if (tz_min > t_enter)
        t_enter = tz_min;
    // find smallest exiting t value
    if (tx_max < ty_max)
        t_exit = tx_max;
    else
        t_exit = ty_max;
    if (tz_max < t_exit)
        t_exit = tz_max;
    return (t_enter < t_exit && t_exit > kEpsilon);
}

void BBox::extend(Geometry *g)
{
    extend(g->getBBox());
}

void BBox::extend(const BBox &b)
{
    pmin = min(b.pmin, pmin);
    pmax = max(b.pmax, pmax);
}

bool BBox::contains(const Point3D &p) const
{
    if (pmin.x <= p.x && p.x <= pmax.x &&
        pmin.y <= p.y && p.y <= pmax.y &&
        pmin.z <= p.z && p.z <= pmax.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BBox::overlaps(Geometry *g)
{
    return this->overlaps(g->getBBox());
}

bool BBox::overlaps(const BBox &b)
{

    // Check overlap in x slap
    // If calling BBox is ahead along x-axis of b BBox
    if (pmax.x >= b.pmax.x)
    {
        // If calling BBox's back along x-axis is behind of b BBox's front along x-axis
        if (pmin.x > b.pmax.x)
        {
            return false;
        }
    }
    // If b BBox is behind along x-axis of calling BBox
    else
    {
        // If b BBox's back along x-axis is behind of calling BBox's front along x-axis
        if (b.pmax.x > pmin.x)
        {
            return false;
        }
    }

    // Check overlap in y slap
    // If calling BBox is ahead along y-axis of b BBox
    if (pmax.y >= b.pmax.y)
    {
        // If calling BBox's back along y-axis is behind of b BBox's front along y-axis
        if (pmin.y > b.pmax.y)
        {
            return false;
        }
    }
    // If b BBox is behind along y-axis of calling BBox
    else
    {
        // If b BBox's back along y-axis is behind of calling BBox's front along y-axis
        if (b.pmax.y > pmin.y)
        {
            return false;
        }
    }

    // Check overlap in z slab
    // If calling BBox is ahead along z-axis of b BBox
    if (pmax.z >= b.pmax.z)
    {
        // If calling BBox's back along x-axis is behind of b BBox's front along x-axis
        if (pmin.z > b.pmax.z)
        {
            return false;
        }
    }
    // If b BBox is behind along x-axis of calling BBox
    else
    {
        // If b BBox's back along x-axis is behind of calling BBox's front along x-axis
        if (b.pmax.z > pmin.z)
        {
            return false;
        }
    }

    // As overlap is along all axis the bounding boxes overlap
    return true;
}