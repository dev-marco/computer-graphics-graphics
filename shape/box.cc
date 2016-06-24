#include "../geometry/intersection.h"
#include "box.h"

namespace Shape {

    bool Box::intersectLine (const Geometry::Line &line, Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {

        unsigned axis_t_min, axis_t_max;
        bool is_t_min_box_min, is_t_max_box_min;

        if (Geometry::Intersection::Line::Box(
            line.getPoint(), line.getDirection(),
            this->getMin(), this->getMax(),
            t_min, axis_t_min, is_t_min_box_min,
            t_max, axis_t_max, is_t_max_box_min
        )) {
            if (axis_t_min == 0) {
                normal_min = is_t_min_box_min ? Geometry::Vec<3>({ -1.0, 0.0, 0.0 }) : Geometry::Vec<3>({ 1.0, 0.0, 0.0 });
            } else if (axis_t_min == 1) {
                normal_min = is_t_min_box_min ? Geometry::Vec<3>({ 0.0, -1.0, 0.0 }) : Geometry::Vec<3>({ 0.0, 1.0, 0.0 });
            } else {
                normal_min = is_t_min_box_min ? Geometry::Vec<3>({ 0.0, 0.0, -1.0 }) : Geometry::Vec<3>({ 0.0, 0.0, 1.0 });
            }

            if (axis_t_max == 0) {
                normal_max = is_t_max_box_min ? Geometry::Vec<3>({ -1.0, 0.0, 0.0 }) : Geometry::Vec<3>({ 1.0, 0.0, 0.0 });
            } else if (axis_t_max == 1) {
                normal_max = is_t_max_box_min ? Geometry::Vec<3>({ 0.0, -1.0, 0.0 }) : Geometry::Vec<3>({ 0.0, 1.0, 0.0 });
            } else {
                normal_max = is_t_max_box_min ? Geometry::Vec<3>({ 0.0, 0.0, -1.0 }) : Geometry::Vec<3>({ 0.0, 0.0, 1.0 });
            }

            if (fix_normals) {
                normal_min.oppose(line.getDirection());
                normal_max.oppose(line.getDirection());
            }

            return true;
        }
        return false;
    }

}
