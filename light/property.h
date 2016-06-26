#ifndef MODULE_GRAPHICS_LIGHT_PROPERTY_H_
#define MODULE_GRAPHICS_LIGHT_PROPERTY_H_

#include "../geometry/geometry.h"

namespace Light {

    template <unsigned SIZE, typename = typename std::enable_if<(1 <= SIZE && SIZE <= 3), bool>::type>
    class Property {

    public:

        Property (void) {}
        virtual ~Property (void) {}

        virtual std::array<float_max_t, SIZE> at (const Geometry::Vec<2> &param, const Geometry::Vec<3> &point) const = 0;

    };

};

#endif
