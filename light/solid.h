#ifndef MODULE_GRAPHICS_SOLID_SOLID_H_
#define MODULE_GRAPHICS_SOLID_SOLID_H_

#include "property.h"

namespace Light {

    template <unsigned SIZE>
    class Solid : public Property<SIZE> {

        std::array<float_max_t, SIZE> value;

    public:
        template <typename T = bool, typename = typename std::enable_if<(SIZE == 1), T>::type>
        Solid (const float_max_t &_value) { value[0] = _value; }

        Solid (const std::array<float_max_t, SIZE> &_value) : value(_value) {};

        inline std::array<float_max_t, SIZE> at (const Geometry::Vec<2> &param, const Geometry::Vec<3> &point) const override { return this->value; };

        inline bool needParameter (void) const override { return false; }

    };

};

#endif
