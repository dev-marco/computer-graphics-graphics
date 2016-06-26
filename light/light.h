#ifndef MODULE_GRAPHICS_LIGHT_LIGHT_H_
#define MODULE_GRAPHICS_LIGHT_LIGHT_H_

#include "../geometry/defaults.h"
#include "../geometry/vec.h"
#include "../pigment/color.h"

namespace Light {

    class Light {
        Geometry::Vec<3> position;
        Pigment::Color color;
        float_max_t constant, linear, quadratic;

    public:
        Light (
            const Geometry::Vec<3> &_position,
            const Pigment::Color &_color,
            float_max_t _constant = 1.0,
            float_max_t _linear = 0.0,
            float_max_t _quadratic = 0.0
        ) :
            position(_position), color(_color), constant(_constant), linear(_linear), quadratic(_quadratic) {};

        inline const Geometry::Vec<3> &getPosition (void) const { return this->position; }
        inline const Pigment::Color &getColor (void) const { return this->color; }
        inline const float_max_t &getConstantAttenuation (void) const { return this->constant; }
        inline const float_max_t &getLinearAttenuation (void) const { return this->linear; }
        inline const float_max_t &getQuadraticAttenuation (void) const { return this->quadratic; }

        inline void setPosition (const Geometry::Vec<3> &_position) { this->position = _position; }
        inline void setColor (const Pigment::Color &_color) { this->color = _color; }
        inline void setConstantAttenuation (const float_max_t &_constant) { this->constant = _constant; }
        inline void setLinearAttenuation (const float_max_t &_linear) { this->linear = _linear; }
        inline void setQuadraticAttenuation (const float_max_t &_quadratic) { this->quadratic = _quadratic; }
    };

};

#endif
