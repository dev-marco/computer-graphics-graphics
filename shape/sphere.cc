#include "../geometry/intersection.h"
#include "../geometry/parametric.h"
#include "sphere.h"

namespace Shape {

    bool Sphere::intersectLine (
        const Geometry::Line &line,
        float_max_t &t_min, float_max_t &t_max,
        bool get_info,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        bool &inside_min, bool &inside_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max
    ) const {
        if (Geometry::Intersection::Line::Sphere(line.getPoint(), line.getDirection(), this->getCenter(), this->getRadius(), t_min, t_max)) {

            if (get_info) {
                const Pigment::Texture *texture = this->getTexture();
                const Light::Surface *surface = this->getSurface();
                const Geometry::Vec<3>
                    point_min = line.at(t_min),
                    point_max = line.at(t_max),
                    &sphere_center = this->getCenter(),
                    &line_direction = line.getDirection();
                const float_max_t &sphere_radius = this->getRadius();
                Geometry::Vec<2> param_min, param_max;

                if (texture->needParameter() || surface->needParameter()) {
                    param_min = Geometry::Parametric::Sphere(sphere_center, sphere_radius, point_min),
                    param_max = Geometry::Parametric::Sphere(sphere_center, sphere_radius, point_max);
                }

                normal_min = (point_min - sphere_center).opposed(line_direction, inside_min).normalized();
                normal_max = (point_max - sphere_center).opposed(line_direction, inside_max).normalized();

                color_min = texture->at(param_min, point_min);
                color_max = texture->at(param_max, point_max);

                material_min = surface->at(param_min, point_min);
                material_max = surface->at(param_max, point_max);
            }

            return true;
        }
        return false;
    }

};
