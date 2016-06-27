#ifndef MODULE_GRAPHICS_SHAPE_POLYHEDRON_H_
#define MODULE_GRAPHICS_SHAPE_POLYHEDRON_H_

#include <vector>
#include "../geometry/plane.h"
#include "shape.h"

namespace Shape {

    class Polyhedron : public Shape {

        std::vector<Geometry::Plane> planes;

    public:

        Polyhedron (const std::vector<Geometry::Plane> &_planes, Pigment::Texture *_texture, Light::Surface *_surface) :
            Shape(_texture, _surface), planes(_planes) {}

        const std::vector<Geometry::Plane> &getPlanes (void) const { return this->planes; }

        void addPlane (const Geometry::Plane &plane) { this->planes.push_back(plane); }
        void popPlane (void) { this->planes.pop_back(); }

        inline bool fit (void) const override { return true; }

        inline const Shape *boundingVolume (void) const override { return this; }

        const char *getType (void) const override { return "polyhedron"; }

        inline Shape *clone (void) const override { return new Polyhedron(this->getPlanes(), this->getTexture(), this->getSurface()); }

        bool intersectLine (
            const Geometry::Line &line,
            float_max_t &t_min, float_max_t &t_max,
            bool get_info,
            Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
            bool &inside_min, bool &inside_max,
            Pigment::Color &color_min, Pigment::Color &color_max,
            Light::Material &material_min, Light::Material &material_max
        ) const override;

    };

};

#endif
