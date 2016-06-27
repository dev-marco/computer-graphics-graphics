#ifndef MODULE_GRAPHICS_SHAPE_SHAPE_H_
#define MODULE_GRAPHICS_SHAPE_SHAPE_H_

#include "../geometry/defaults.h"
#include "../geometry/vec.h"
#include "../geometry/line.h"
#include "../pigment/color.h"
#include "../pigment/texture.h"
#include "../light/material.h"
#include "../light/surface.h"

namespace Shape {

    class Shape {

        Pigment::Texture *texture;
        Light::Surface *surface;

    public:

        constexpr Shape (Pigment::Texture *_texture, Light::Surface *_surface) :
            texture(_texture), surface(_surface) {}

        virtual ~Shape (void) {}

        virtual Pigment::Texture *getTexture (void) const { return this->texture; }
        virtual void setTexture (Pigment::Texture *_texture) { this->texture = _texture; }

        virtual Light::Surface *getSurface (void) const { return this->surface; }
        virtual void setSurface (Light::Surface *_surface) { this->surface = _surface; }

        virtual bool fit (void) const = 0;

        virtual const Shape *boundingVolume (void) const = 0;

        virtual const char *getType (void) const = 0;

        virtual Shape *clone (void) const = 0;

        virtual bool intersectLine (
            const Geometry::Line &line,
            float_max_t &t_min, float_max_t &t_max,
            bool get_info,
            Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
            bool &inside_min, bool &inside_max,
            Pigment::Color &color_min, Pigment::Color &color_max,
            Light::Material &material_min, Light::Material &material_max
        ) const = 0;

    };
}

#endif
