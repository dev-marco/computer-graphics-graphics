#ifndef MODULE_GRAPHICS_SHAPE_CYLINDER_H_
#define MODULE_GRAPHICS_SHAPE_CYLINDER_H_

#include "shape.h"

namespace Shape {

    class Cylinder : public Shape {

        Geometry::Vec<3> bottom, top, direction, delta;
        float_max_t radius, height, height2;

        inline void updateDirection (void) {
            this->delta = this->getTop() - this->getBottom();
            this->height2 = this->delta.length2();
            this->height = std::sqrt(this->height2);
            this->direction = this->delta.resized(this->height, 1.0);
        }

    public:

        Cylinder (const Geometry::Vec<3> &_bottom, const Geometry::Vec<3> &_top, float_max_t _radius, Pigment::Texture *_texture, Light::Surface *_surface) :
            Shape(_texture, _surface), bottom(_bottom), top(_top), radius(_radius) { this->updateDirection(); }

        inline const Geometry::Vec<3> &getBottom (void) const { return this->bottom; }
        inline const Geometry::Vec<3> &getTop (void) const { return this->top; }
        inline const Geometry::Vec<3> &getDirection (void) const { return this->direction; }
        inline const Geometry::Vec<3> &getDelta (void) const { return this->delta; }
        inline const float_max_t &getRadius (void) const { return this->radius; }
        inline const float_max_t &getHeight (void) const { return this->height; }
        inline const float_max_t &getHeight2 (void) const { return this->height2; }

        inline void setBottom (const Geometry::Vec<3> &_bottom) { this->bottom = _bottom; this->updateDirection(); }
        inline void setTop (const Geometry::Vec<3> &_top) { this->top = _top; this->updateDirection(); }
        inline void setRadius (float_max_t _radius) { this->radius = _radius; }

        inline bool fit (void) const override { return true; }

        inline const Shape *boundingVolume (void) const override { return this; }

        const char *getType (void) const override { return "cylinder"; };

        inline Shape *clone (void) const override { return new Cylinder(this->getBottom(), this->getTop(), this->getRadius(), this->getTexture(), this->getSurface()); }

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
