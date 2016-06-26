#include "../geometry/intersection.h"
#include "../geometry/parametric.h"
#include "polyhedron.h"

namespace Shape {

    bool Polyhedron::intersectLine (
        const Geometry::Line &line,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max,
        float_max_t &t_min, float_max_t &t_max,
        bool fix_normals
    ) const {

        unsigned face_min, face_max;
        const std::vector<Geometry::Plane> &planes = this->getPlanes();

        if (Geometry::Intersection::Line::Polyhedron(
            line.getPoint(), line.getDirection(),
            planes,
            t_min, face_min, t_max, face_max
        )) {

            if (t_min > -std::numeric_limits<float_max_t>::infinity()) {
                const Geometry::Vec<3> point_min = line.at(t_min);
                const Geometry::Vec<2> param_min = Geometry::Parametric::Plane(planes[face_min], point_min);
                color_min = this->getTexture()->at(param_min, point_min);
                material_min = this->getSurface()->at(param_min, point_min);
                normal_min = fix_normals ? planes[face_min].getNormal().opposed(line.getDirection()) : planes[face_min].getNormal();
            }

            if (t_max < std::numeric_limits<float_max_t>::infinity()) {
                const Geometry::Vec<3> point_max = line.at(t_max);
                const Geometry::Vec<2> param_max = Geometry::Parametric::Plane(planes[face_max], point_max);
                color_max = this->getTexture()->at(param_max, point_max);
                material_max = this->getSurface()->at(param_max, point_max);
                normal_max = fix_normals ? planes[face_max].getNormal().opposed(line.getDirection()) : planes[face_max].getNormal();
            }

            return true;
        }
        return false;
    }

};
