#ifndef MODULE_GRAPHICS_PIGMENT_PROCEDURAL_H_
#define MODULE_GRAPHICS_PIGMENT_PROCEDURAL_H_

#include <functional>
#include "../geometry/defaults.h"
#include "texture.h"

namespace Pigment {

    class Procedural : public Texture {

        std::function<Color(const Geometry::Vec<2> &param)> procedure;

    public:
        Procedural (
            const std::function<Color(const Geometry::Vec<2> &param)> &_procedure,
            const float_max_t &_s_size = 1.0,
            const float_max_t &_t_size = 1.0,
            const float_max_t &_s_offset = 0.0,
            const float_max_t &_t_offset = 0.0
        ) :
            Texture(_s_size, _t_size, _s_offset, _t_offset), procedure(_procedure) {}

        inline Color at (const Geometry::Vec<2> &param) const override {
            return this->procedure({
                param[0] * this->getInverseSSize() + this->getSOffset(),
                param[1] * this->getInverseTSize() + this->getTOffset()
            });
        }
    };

};

#endif
