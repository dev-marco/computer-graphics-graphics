#ifndef MODULE_GRAPHICS_SHAPE_CSG_TREE_H_
#define MODULE_GRAPHICS_SHAPE_CSG_TREE_H_

#include "shape.h"

namespace Shape {

    class CSGTree : public Shape {

    public:

        enum Type {
            UNION,
            INTERSECTION,
            SUBTRACTION
        };

    private:

        Shape *first, *second;
        Type operation;

    public:

        constexpr CSGTree (Shape *_first, Type _operation, Shape *_second, Pigment::Texture *_texture = nullptr, Light::Surface *_surface = nullptr) :
            Shape(_texture, _surface), first(_first), second(_second), operation(_operation) {}

        inline Shape *getFirst (void) const { return this->first; }
        inline Shape *getSecond (void) const { return this->second; }
        inline Type getOperation (void) const { return this->operation; }

        inline bool fit (void) const override { return true; }

        inline const Shape *boundingVolume (void) const override { return this; }

        inline const char *getType (void) const override { return "csg_tree"; }

        inline Shape *clone (void) const override { return new CSGTree(this->getFirst(), this->getOperation(), this->getSecond(), this->getTexture(), this->getSurface()); }

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
