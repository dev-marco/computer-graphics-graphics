#ifndef MODULE_GRAPHICS_PIGMENT_TEXTURE_H_
#define MODULE_GRAPHICS_PIGMENT_TEXTURE_H_

#include "../geometry/plane.h"
#include "color.h"

namespace Pigment {

    class Texture {

        float_max_t s_size, s_offset, inv_s_size, t_size, t_offset, inv_t_size;

    public:
        Texture (
            const float_max_t &_s_size = 1.0,
            const float_max_t &_t_size = 1.0,
            const float_max_t &_s_offset = 0.0,
            const float_max_t &_t_offset = 0.0
        ) :
            s_size(_s_size), s_offset(_s_offset), inv_s_size(1.0 / _s_size),
            t_size(_t_size), t_offset(_t_offset), inv_t_size(1.0 / _t_size) {}

        virtual ~Texture (void) {};

        const float_max_t &getSSize (void) const { return this->s_size; }
        const float_max_t &getInverseSSize (void) const { return this->inv_s_size; }

        const float_max_t &getTSize (void) const { return this->t_size; }
        const float_max_t &getInverseTSize (void) const { return this->inv_t_size; }

        const float_max_t &getSOffset (void) const { return this->s_offset; }
        const float_max_t &getTOffset (void) const { return this->t_offset; }

        void setSSize (const float_max_t &_s_size) { this->s_size = _s_size, this->inv_s_size = 1.0 / _s_size; }
        void setTSize (const float_max_t &_t_size) { this->t_size = _t_size, this->inv_t_size = 1.0 / _t_size; }

        virtual Color at (const Geometry::Vec<2> &param) const = 0;
        virtual Color at (const Geometry::Vec<2> &param, const Geometry::Vec<3> &point) const { return this->at(param); }

        inline virtual bool needParameter (void) const { return true; }

    };

};

#endif
