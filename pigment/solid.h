#ifndef MODULE_GRAPHICS_PIGMENT_SOLID_H_
#define MODULE_GRAPHICS_PIGMENT_SOLID_H_

#include "texture.h"

namespace Pigment {

    class Solid : public Texture {

        Color color;

    public:
        Solid (const Color &_color) :
            color(_color) {}

        inline const Color &getColor (void) const { return this->color; }

        inline Color at (const Geometry::Vec<2> &param) override { return this->getColor(); }
    };

};

#endif
