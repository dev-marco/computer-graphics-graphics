#include "../geometry/intersection.h"
#include "../geometry/parametric.h"
#include "sphere.h"

namespace Shape {

    bool Sphere::intersectLine (
        const Geometry::Line &line,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max,
        float_max_t &t_min, float_max_t &t_max,
        bool fix_normals
    ) const {
        if (Geometry::Intersection::Line::Sphere(line.getPoint(), line.getDirection(), this->getCenter(), this->getRadius(), t_min, t_max)) {

            const Pigment::Texture *texture = this->getTexture();
            const Light::Surface *surface = this->getSurface();
            const Geometry::Vec<3>
                point_min = line.at(t_min),
                point_max = line.at(t_max),
                &sphere_center = this->getCenter(),
                &line_direction = line.getDirection();
            const float_max_t &sphere_radius = this->getRadius();
            const Geometry::Vec<2>
                param_min = Geometry::Parametric::Sphere(sphere_center, sphere_radius, point_min),
                param_max = Geometry::Parametric::Sphere(sphere_center, sphere_radius, point_max);

            normal_min = (point_min - sphere_center).normalized();
            normal_max = (point_max - sphere_center).normalized();

            if (fix_normals) {
                normal_min.oppose(line_direction);
                normal_max.oppose(line_direction);
            }

            color_min = texture->at(param_min, point_min);
            color_max = texture->at(param_max, point_max);

            material_min = surface->at(param_min, point_min);
            material_max = surface->at(param_max, point_max);

            return true;
        }
        return false;
    }

};
