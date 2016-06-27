#include "../geometry/intersection.h"
#include "../geometry/parametric.h"
#include "box.h"

namespace Shape {

    bool Box::intersectLine (
        const Geometry::Line &line,
        float_max_t &t_min, float_max_t &t_max,
        bool get_info,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        bool &inside_min, bool &inside_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max
    ) const {

        unsigned axis_t_min, axis_t_max;
        bool is_t_min_box_min, is_t_max_box_min;

        if (Geometry::Intersection::Line::Box(
            line.getPoint(), line.getDirection(),
            this->getMin(), this->getMax(),
            t_min, axis_t_min, is_t_min_box_min,
            t_max, axis_t_max, is_t_max_box_min
        )) {

            if (get_info) {
                const Pigment::Texture *texture = this->getTexture();
                const Light::Surface *surface = this->getSurface();

                const std::array<Geometry::Plane, 6> &planes = this->getPlanes();

                const Geometry::Vec<3>
                    point_min = line.at(t_min),
                    point_max = line.at(t_max);

                Geometry::Vec<2> param_min, param_max;
                unsigned min_index, max_index;

                if (axis_t_min == 0) {
                    min_index = is_t_min_box_min ? 0 : 1;
                } else if (axis_t_min == 1) {
                    min_index = is_t_min_box_min ? 2 : 3;
                } else {
                    min_index = is_t_min_box_min ? 4 : 5;
                }

                if (axis_t_max == 0) {
                    max_index = is_t_max_box_min ? 0 : 1;
                } else if (axis_t_max == 1) {
                    max_index = is_t_max_box_min ? 2 : 3;
                } else {
                    max_index = is_t_max_box_min ? 4 : 5;
                }

                if (texture->needParameter() || surface->needParameter()) {
                    param_min = Geometry::Parametric::Plane(planes[min_index], point_min);
                    param_max = Geometry::Parametric::Plane(planes[max_index], point_max);
                }

                normal_min = planes[min_index].getNormal().opposed(line.getDirection(), inside_min);
                normal_max = planes[max_index].getNormal().opposed(line.getDirection(), inside_max);

                color_min = texture->at(param_min, point_min);
                color_max = texture->at(param_max, point_max);

                material_min = surface->at(param_min, point_min);
                material_max = surface->at(param_max, point_max);
            }

            return true;
        }
        return false;
    }

}
