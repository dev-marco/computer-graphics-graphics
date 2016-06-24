#ifndef MODULE_GRAPHICS_PIGMENT_PROCEDURAL_H_
#define MODULE_GRAPHICS_PIGMENT_PROCEDURAL_H_

#include <functional>
#include "../geometry/defaults.h"
#include "texture.h"

namespace Pigment {

    class Procedural : public Texture {

        std::function<Color(const Geometry::Vec<2> &param)> procedure;

    public:
        Procedural (const std::function<Color(const Geometry::Vec<2> &param)> &_procedure) :
            procedure(_procedure) {}

        inline Color at (const Geometry::Vec<2> &param) override { return this->procedure(param); }
    };

};

#endif
