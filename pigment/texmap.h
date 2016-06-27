#ifndef MODULE_GRAPHICS_PIGMENT_TEXMAP_H_
#define MODULE_GRAPHICS_PIGMENT_TEXMAP_H_

#include "texture.h"

namespace Pigment {
    template <typename TEXT, typename = typename std::enable_if<std::is_base_of<Texture, TEXT>::value, TEXT>::type>
    class TexMap : public TEXT {

        Geometry::Vec<4> P0, P1;

    public:
        template <class T = TEXT, class ... Args>
        TexMap (const Geometry::Vec<4> &_P0, const Geometry::Vec<4> &_P1, Args && ... args) :
            TEXT(std::forward<Args>(args)...), P0(_P0), P1(_P1) {}

        inline Color at (const Geometry::Vec<2> &param, const Geometry::Vec<3> &point) const override {
            return TEXT::at({ this->P0.dot({ point[0], point[1], point[2], 1.0 }), this->P1.dot({ point[0], point[1], point[2], 1.0 }) }, point);
        }

        inline bool needParameter (void) const override { return false; }

    };
}

#endif
