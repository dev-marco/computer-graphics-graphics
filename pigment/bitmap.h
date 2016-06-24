#ifndef MODULE_GRAPHICS_PIGMENT_BITMAP_H_
#define MODULE_GRAPHICS_PIGMENT_BITMAP_H_

#include "../geometry/vec.h"
#include "image.h"
#include "texture.h"

namespace Pigment {

    class Bitmap : Texture {

        Graphics::Image image;
        Geometry::Vec<4> P0, P1;

    public:
        Bitmap (const std::string &file, const Geometry::Vec<4> _P0, const Geometry::Vec<4> _P1) :
            image(Graphics::Image::readPPM(file)), P0(_P0), P1(_P1) {};

    };

};

#endif
