#include "../geometry/intersection.h"
#include "sphere.h"

namespace Shape {

    Geometry::Vec<2> Sphere::param (const Geometry::Vec<3> &point) const {
        const Geometry::Vec<3> diff = point - this->getCenter();
        return { std::acos(Geometry::clamp(diff[2] / this->getRadius(), -1.0, 1.0)) / Geometry::PI, std::atan2(diff[1], diff[0]) / Geometry::TWO_PI };
    }

    bool Sphere::intersectLine (const Geometry::Line &line, Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {
        if (Geometry::Intersection::Line::Sphere(line.getPoint(), line.getDirection(), this->getCenter(), this->getRadius(), t_min, t_max)) {
            normal_min = (line.at(t_min) - this->getCenter()).normalized();
            normal_max = (line.at(t_max) - this->getCenter()).normalized();

            this->param(line.at(t_min));

            if (fix_normals) {
                normal_min.oppose(line.getDirection());
                normal_max.oppose(line.getDirection());
            }

            return true;
        }
        return false;
    }

};
