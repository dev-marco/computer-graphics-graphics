#include "../geometry/intersection.h"
#include "cylinder.h"

namespace Shape {

    Geometry::Vec<2> Cylinder::param (const Geometry::Vec<3> &point) const {
        const Geometry::Vec<3> diff = point - this->getBottom();
        return { std::atan2(diff[1], diff[0]) / Geometry::TWO_PI, diff[2] / this->getHeight() };
    }

    bool Cylinder::intersectLine (const Geometry::Line &line, Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {

        bool is_t_min_top_cap, is_t_min_bottom_cap, is_t_max_top_cap, is_t_max_bottom_cap;

        if (Geometry::Intersection::Line::Cylinder(
            line.getPoint(), line.getDirection(),
            this->getBottom(), this->getTop(), this->getRadius(),
            t_min, is_t_min_top_cap, is_t_min_bottom_cap,
            t_max, is_t_max_top_cap, is_t_max_bottom_cap
        )) {
            static Geometry::Vec<3> direction, delta;
            direction = this->getDirection();

            this->param(line.at(t_min));

            if (is_t_min_top_cap) {
                normal_min = direction;
            } else if (is_t_min_bottom_cap) {
                normal_min = -direction;
            } else {
                delta = line.at(t_min) - this->getTop();
                normal_min = delta - delta.dot(direction) * direction;
            }

            if (is_t_max_top_cap) {
                normal_max = direction;
            } else if (is_t_max_bottom_cap) {
                normal_max = -direction;
            } else {
                delta = line.at(t_max) - this->getTop();
                normal_max = delta - delta.dot(direction) * direction;
            }

            if (fix_normals) {
                normal_min.oppose(line.getDirection());
                normal_max.oppose(line.getDirection());
            }

            return true;
        }
        return false;
    }

};
