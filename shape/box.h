#ifndef MODULE_GRAPHICS_SHAPE_BOX_H_
#define MODULE_GRAPHICS_SHAPE_BOX_H_

#include "../geometry/defaults.h"
#include "../geometry/vec.h"
#include "../geometry/line.h"
#include "../geometry/plane.h"
#include "shape.h"

namespace Shape {

    class Box : public Shape {

        Geometry::Vec<3> min, max;
        std::array<Geometry::Plane, 6> planes;

        void updateMinPlanes (void) {
            this->planes[0] = Geometry::Plane({ -1.0, 0.0, 0.0 }, this->getMin());
            this->planes[2] = Geometry::Plane({ 0.0, -1.0, 0.0 }, this->getMin());
            this->planes[4] = Geometry::Plane({ 0.0, 0.0, -1.0 }, this->getMin());
        }

        void updateMaxPlanes (void) {
            this->planes[1] = Geometry::Plane({ 1.0, 0.0, 0.0 }, this->getMax());
            this->planes[3] = Geometry::Plane({ 0.0, 1.0, 0.0 }, this->getMax());
            this->planes[5] = Geometry::Plane({ 0.0, 0.0, 1.0 }, this->getMax());
        }

        public:

            Box (const Geometry::Vec<3> &_min, const Geometry::Vec<3> &_max, Pigment::Texture *_texture, Light::Surface *_surface) :
                Shape(_texture, _surface), min(_min), max(_max) { this->updateMinPlanes(), this->updateMaxPlanes(); }

            inline const Geometry::Vec<3> &getMin (void) const { return this->min; }
            inline const Geometry::Vec<3> &getMax (void) const { return this->max; }

            inline void setMin (const Geometry::Vec<3> &_min) { this->min = _min, this->updateMinPlanes(); }
            inline void setMax (const Geometry::Vec<3> &_max) { this->max = _max, this->updateMaxPlanes(); }

            const std::array<Geometry::Plane, 6> &getPlanes (void) const { return this->planes; }

            inline const Shape *boundingVolume (void) const override { return this; }

            const char *getType (void) const override { return "box"; }

            inline Shape *clone (void) const override { return new Box(this->getMin(), this->getMax(), this->getTexture(), this->getSurface()); }

            inline bool fit (void) const override { return true; }

            bool intersectLine (
                const Geometry::Line &line,
                Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
                Pigment::Color &color_min, Pigment::Color &color_max,
                Light::Material &material_min, Light::Material &material_max,
                float_max_t &t_min, float_max_t &t_max,
                bool fix_normals = true
            ) const override;

    };
};

#endif
