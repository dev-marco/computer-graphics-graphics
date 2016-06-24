#include "../geometry/intersection.h"
#include "polyhedron.h"

namespace Shape {

    bool Polyhedron::intersectLine (const Geometry::Line &line, Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {

        unsigned face_min, face_max;
        const std::vector<Geometry::Plane> &planes = this->getPlanes();

        if (Geometry::Intersection::Line::Polyhedron(
            line.getPoint(), line.getDirection(),
            planes,
            t_min, face_min, t_max, face_max
        )) {
            if (fix_normals) {
                normal_min = planes[face_min].getNormal().opposed(line.getDirection());
                normal_max = planes[face_max].getNormal().opposed(line.getDirection());
            } else {
                normal_min = planes[face_min].getNormal();
                normal_max = planes[face_max].getNormal();
            }
            return true;
        }
        return false;
    }

};
