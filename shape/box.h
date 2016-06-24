#ifndef MODULE_GRAPHICS_GEOMETRY_BOX_H_
#define MODULE_GRAPHICS_GEOMETRY_BOX_H_

#include "../geometry/defaults.h"
#include "../geometry/vec.h"
#include "../geometry/line.h"
#include "shape.h"

namespace Shape {

    class Box : public Shape {

        Geometry::Vec<3> min, max;

        public:

            Box (const Geometry::Vec<3> &_min, const Geometry::Vec<3> &_max) :
                min(_min), max(_max) {}

            inline const Geometry::Vec<3> &getMin (void) const { return this->min; }
            inline const Geometry::Vec<3> &getMax (void) const { return this->max; }

            inline void setMin (const Geometry::Vec<3> &_min) { this->min = _min; }
            inline void setMax (const Geometry::Vec<3> &_max) { this->max = _max; }

            inline const Shape *boundingVolume (void) const override { return this; }

            const char *getType (void) const override { return "box"; }

            inline Shape *clone (void) const override { return new Box(this->getMin(), this->getMax()); }

            inline bool fit (void) const override { return true; }

            bool intersectLine (const Geometry::Line &line, Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals = true) const override;

    };
};

#endif
