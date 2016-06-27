#include "../geometry/intersection.h"
#include "../geometry/parametric.h"
#include "polyhedron.h"

namespace Shape {

    bool Polyhedron::intersectLine (
        const Geometry::Line &line,
        float_max_t &t_min, float_max_t &t_max,
        bool get_info,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        bool &inside_min, bool &inside_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max
    ) const {

        unsigned face_min, face_max;
        const std::vector<Geometry::Plane> &planes = this->getPlanes();

        if (Geometry::Intersection::Line::Polyhedron(
            line.getPoint(), line.getDirection(),
            planes,
            t_min, face_min, t_max, face_max
        )) {

            if (get_info) {

                const Pigment::Texture *texture = this->getTexture();
                const Light::Surface *surface = this->getSurface();

                if (t_min > -std::numeric_limits<float_max_t>::infinity()) {

                    const Geometry::Vec<3> point_min = line.at(t_min);
                    Geometry::Vec<2> param_min;

                    if (texture->needParameter() || surface->needParameter()) {
                        param_min = Geometry::Parametric::Plane(planes[face_min], point_min);
                    }

                    normal_min = planes[face_min].getNormal().opposed(line.getDirection(), inside_min);
                    color_min = texture->at(param_min, point_min);
                    material_min = surface->at(param_min, point_min);
                }

                if (t_max < std::numeric_limits<float_max_t>::infinity()) {

                    const Geometry::Vec<3> point_max = line.at(t_max);
                    Geometry::Vec<2> param_max;

                    if (texture->needParameter() || surface->needParameter()) {
                        param_max = Geometry::Parametric::Plane(planes[face_max], point_max);
                    }

                    normal_max = planes[face_max].getNormal().opposed(line.getDirection(), inside_max);
                    color_max = texture->at(param_max, point_max);
                    material_max = surface->at(param_max, point_max);
                }
            }

            return true;
        }
        return false;
    }

};
