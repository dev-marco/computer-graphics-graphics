#include "../geometry/intersection.h"
#include "../geometry/parametric.h"
#include "cylinder.h"

namespace Shape {

    bool Cylinder::intersectLine (
        const Geometry::Line &line,
        float_max_t &t_min, float_max_t &t_max,
        bool get_info,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        bool &inside_min, bool &inside_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max
    ) const {

        bool is_t_min_top_cap, is_t_min_bottom_cap, is_t_max_top_cap, is_t_max_bottom_cap;

        if (Geometry::Intersection::Line::Cylinder(
            line.getPoint(), line.getDirection(),
            this->getBottom(), this->getDelta(), this->getHeight2(), this->getRadius(),
            t_min, is_t_min_top_cap, is_t_min_bottom_cap,
            t_max, is_t_max_top_cap, is_t_max_bottom_cap
        )) {

            if (get_info) {

                const Pigment::Texture *texture = this->getTexture();
                const Light::Surface *surface = this->getSurface();

                const Geometry::Vec<3>
                    point_min = line.at(t_min),
                    point_max = line.at(t_max),
                    &cylinder_direction = this->getDirection(),
                    &cylinder_bottom = this->getBottom(),
                    &line_direction = line.getDirection();

                const float_max_t &cylinder_height = this->getHeight();
                Geometry::Vec<2> param_min, param_max;

                if (texture->needParameter() || surface->needParameter()) {
                    param_min = Geometry::Parametric::Cylinder(cylinder_bottom, cylinder_direction, cylinder_height, point_min),
                    param_max = Geometry::Parametric::Cylinder(cylinder_bottom, cylinder_direction, cylinder_height, point_max);
                }

                if (is_t_min_top_cap) {
                    normal_min = cylinder_direction;
                } else if (is_t_min_bottom_cap) {
                    normal_min = -cylinder_direction;
                } else {
                    const Geometry::Vec<3> delta = point_min - cylinder_bottom;
                    normal_min = delta - delta.dot(cylinder_direction) * cylinder_direction;
                }

                if (is_t_max_top_cap) {
                    normal_max = cylinder_direction;
                } else if (is_t_max_bottom_cap) {
                    normal_max = -cylinder_direction;
                } else {
                    const Geometry::Vec<3> delta = point_max - cylinder_bottom;
                    normal_max = delta - delta.dot(cylinder_direction) * cylinder_direction;
                }

                normal_min.oppose(line_direction, inside_min);
                normal_max.oppose(line_direction, inside_max);

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
