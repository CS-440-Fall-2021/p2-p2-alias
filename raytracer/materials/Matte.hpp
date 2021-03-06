#pragma once

#include "Material.hpp"

#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Shadeinfo.hpp"
#include "../BRDF/Lambertian.hpp"
class Matte : public Material {
public:
    // Constructors.
    Matte();
    Matte(Lambertian* ambient_brdf_, Lambertian* diffuse_brdf_);

    // Copy constuctor and assignment operator.
    Matte(const Matte &other) = default;
    Matte &operator=(const Matte &other) = default;

    // Destructor.
    virtual ~Matte() = default;

    virtual RGBColor shade(ShadeInfo &sinfo) override;

    // Access Methods
    void set_ka(const double ka);
    void set_kd(const double kd);
    void set_cd(const RGBColor& c);

private:
  Lambertian* ambient_brdf;
  Lambertian* diffuse_brdf;
};
