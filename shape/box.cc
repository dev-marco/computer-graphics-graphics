#include "../geometry/intersection.h"
#include "../geometry/parametric.h"
#include "box.h"

namespace Shape {

    bool Box::intersectLine (
        const Geometry::Line &line,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max,
        float_max_t &t_min, float_max_t &t_max,
        bool fix_normals
    ) const {

        unsigned axis_t_min, axis_t_max;
        bool is_t_min_box_min, is_t_max_box_min;

        if (Geometry::Intersection::Line::Box(
            line.getPoint(), line.getDirection(),
            this->getMin(), this->getMax(),
            t_min, axis_t_min, is_t_min_box_min,
            t_max, axis_t_max, is_t_max_box_min
        )) {

            const Pigment::Texture *texture = this->getTexture();
            const Light::Surface *surface = this->getSurface();

            const std::array<Geometry::Plane, 6> &planes = this->getPlanes();

            const Geometry::Vec<3>
                point_min = line.at(t_min),
                point_max = line.at(t_max);

            Geometry::Vec<2> param_min, param_max;

            if (axis_t_min == 0) {
                if (is_t_min_box_min) {
                    param_min = Geometry::Parametric::Plane(planes[0], point_min);
                    normal_min = Geometry::Vec<3>({ -1.0, 0.0, 0.0 });
                } else {
                    param_min = Geometry::Parametric::Plane(planes[1], point_min);
                    normal_min = Geometry::Vec<3>({ 1.0, 0.0, 0.0 });
                }
            } else if (axis_t_min == 1) {
                if (is_t_min_box_min) {
                    param_min = Geometry::Parametric::Plane(planes[2], point_min);
                    normal_min = Geometry::Vec<3>({ 0.0, -1.0, 0.0 });
                } else {
                    param_min = Geometry::Parametric::Plane(planes[3], point_min);
                    normal_min = Geometry::Vec<3>({ 0.0, 1.0, 0.0 });
                }
            } else {
                if (is_t_min_box_min) {
                    param_min = Geometry::Parametric::Plane(planes[4], point_min);
                    normal_min = Geometry::Vec<3>({ 0.0, 0.0, -1.0 });
                } else {
                    param_min = Geometry::Parametric::Plane(planes[5], point_min);
                    normal_min = Geometry::Vec<3>({ 0.0, 0.0, 1.0 });
                }
            }

            if (axis_t_max == 0) {
                if (is_t_max_box_min) {
                    param_max = Geometry::Parametric::Plane(planes[0], point_max);
                    normal_max = Geometry::Vec<3>({ -1.0, 0.0, 0.0 });
                } else {
                    param_max = Geometry::Parametric::Plane(planes[1], point_max);
                    normal_max = Geometry::Vec<3>({ 1.0, 0.0, 0.0 });
                }
            } else if (axis_t_max == 1) {
                if (is_t_max_box_min) {
                    param_max = Geometry::Parametric::Plane(planes[2], point_max);
                    normal_max = Geometry::Vec<3>({ 0.0, -1.0, 0.0 });
                } else {
                    param_max = Geometry::Parametric::Plane(planes[3], point_max);
                    normal_max = Geometry::Vec<3>({ 0.0, 1.0, 0.0 });
                }
            } else {
                if (is_t_max_box_min) {
                    param_max = Geometry::Parametric::Plane(planes[4], point_max);
                    normal_max = Geometry::Vec<3>({ 0.0, 0.0, -1.0 });
                } else {
                    param_max = Geometry::Parametric::Plane(planes[5], point_max);
                    normal_max = Geometry::Vec<3>({ 0.0, 0.0, 1.0 });
                }
            }

            color_min = texture->at(param_min, point_min);
            color_max = texture->at(param_max, point_max);

            material_min = surface->at(param_min, point_min);
            material_max = surface->at(param_max, point_max);

            if (fix_normals) {
                normal_min.oppose(line.getDirection());
                normal_max.oppose(line.getDirection());
            }

            return true;
        }
        return false;
    }

}
