#include "Triangle.hpp"

Triangle::Triangle()
{
    v0 = Point3D(0, 0, 0);
    v1 = Point3D(0, 0, 0);
    v2 = Point3D(0, 0, 0);
    n0 = Vector3D(0, 0, 0);
    n1 = Vector3D(0, 0, 0);
    n2 = Vector3D(0, 0, 0);
}

Triangle::Triangle(const Point3D &a, const Point3D &b, const Point3D &c, const Vector3D& n)
{
    v0 = a;
    v1 = b;
    v2 = c;
    n0 = n;
    n1 = n;
    n2 = n;
}

Triangle::Triangle(const Point3D &a, const Point3D &b, const Point3D &c, const Vector3D& n0_, const Vector3D& n1_, const Vector3D& n2_)
{
    v0 = a;
    v1 = b;
    v2 = c;
    n0 = n0_;
    n1 = n1_;
    n2 = n2_;
}

Triangle::Triangle(const Triangle &object)
{
    v0 = object.v0;
    v1 = object.v1;
    v2 = object.v2;
    n0 = object.n0;
    n1 = object.n1;
    n2 = object.n2;
}

Triangle &Triangle::operator=(const Triangle &rhs)
{
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    n0 = rhs.n0;
    n1 = rhs.n1;
    n2 = rhs.n2;
    return *this;
}

std::string Triangle::to_string() const
{
    std::string out = "Vertex 0:" + v0.to_string() + "\n" +
                      "Vertex 1:" + v1.to_string() + "\n" +
                      "Vertex 2:" + v2.to_string() + "\n" +
                      "Normal 0:" + n0.to_string() + "\n";
                      "Normal 1:" + n1.to_string() + "\n";
                      "Normal 2:" + n2.to_string() + "\n";

    return out;
}

bool Triangle::hit(const Ray &ray, double &t, ShadeInfo &s_) const
{

    double a = v0.x - v1.x,     b = v0.x - v2.x,    c = ray.d.x,    d = v0.x - ray.o.x;
    double e = v0.y - v1.y,     f = v0.y - v2.y,    g = ray.d.y,    h = v0.y - ray.o.y;
    double i = v0.z - v1.z,     j = v0.z - v2.z,    k = ray.d.z,    l = v0.z - ray.o.z;
    double m = f * k - g * j,   n = h * k - g * l,  p = f * l - h * j;
    double q = g * i - e * k,   r = e * l - h * i,  s = e * j - f * i;
    double inv_denom = 1.0 / (a * m + b * q + c * s);
    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0 || beta > 1.0)
        return (false);
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;
    if (gamma < 0.0 || gamma > 1.0)
        return (false);
    if (beta + gamma > 1.0)
        return (false);
    double e3 = a * p - b * r + d * s;
    double t_ = e3 * inv_denom;
    if ((t_ < kEpsilon) & (t_ < t))
        return (false);

    t = t_;
    s_.normal = interpolate_normals(beta, gamma);
    s_.hit_point = ray.o + t_ * ray.d;
    s_.hit = true;
    s_.ray = ray;
    s_.t = t_;
    s_.material_ptr = this->get_material();
    return (true);
}

// Get bounding box.
BBox Triangle::getBBox() const
{
    Point3D tempMin = min(v0, v1);
    Point3D PMIN = min(tempMin, v2);
    Point3D tempMax = max(v0, v1);
    Point3D PMAX = max(tempMax, v2);

    return BBox(PMIN, PMAX);
}

Vector3D Triangle::interpolate_normals(double beta, double gamma) const{
    Vector3D norm((1 - beta - gamma) * n0
                    + beta * n1
                    + gamma * n2);
    return norm.hat();
}

Triangle *Triangle::clone() const
{
    return (new Triangle(*this));
}
