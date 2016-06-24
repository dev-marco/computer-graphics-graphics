#ifndef MODULE_GRAPHICS_PIGMENT_TEXTURE_H_
#define MODULE_GRAPHICS_PIGMENT_TEXTURE_H_

#include "color.h"

namespace Pigment {

    class Texture {

    public:
        Texture (void) {}
        virtual ~Texture (void) {}

        virtual Color at (const Geometry::Vec<2> &param) = 0;
    };

};

#endif
