#ifndef MODULE_GRAPHICS_PIGMENT_COLOR_H_
#define MODULE_GRAPHICS_PIGMENT_COLOR_H_

#include <opencv2/opencv.hpp>
#include "../geometry/defaults.h"
#include "../geometry/vec.h"

namespace Pigment {

    class Color : public Geometry::Vec<4> {

    public:

        inline static Color rgb (unsigned char red, unsigned char green, unsigned char blue) { return Color(red / 255.0, green / 255.0, blue / 255.0); }
        inline static Color rgba (unsigned char red, unsigned char green, unsigned char blue, float_max_t alpha) { return Color(red / 255.0, green / 255.0, blue / 255.0, alpha); }

        Color (void) : Geometry::Vec<4>(0.0) {}
        Color (const Vec<4> &_vec) : Geometry::Vec<4>(_vec) {}
        Color (const Vec<3> &_vec) :
            Geometry::Vec<4>({ _vec[0], _vec[1], _vec[2], 1.0 }) {}
        Color (const cv::Vec3b &_vec) :
            Geometry::Vec<4>({ _vec[2] / 255.0, _vec[1] / 255.0, _vec[0] / 255.0, 1.0 }) {}

        operator cv::Vec3b (void) const { return {
            static_cast<unsigned char>(this->blue() * 255.0),
            static_cast<unsigned char>(this->green() * 255.0),
            static_cast<unsigned char>(this->red() * 255.0)
        }; }

        Color (float_max_t red, float_max_t green, float_max_t blue, float_max_t alpha = 1.0) :
            Geometry::Vec<4>({ red, green, blue, alpha }) {};

        inline float_max_t red (void) const { return (*this)[0]; }
        inline float_max_t green (void) const { return (*this)[1]; }
        inline float_max_t blue (void) const { return (*this)[2]; }
        inline float_max_t alpha (void) const { return (*this)[3]; }

        inline Color intervalFixed (void) { return this->allClamped(0.0, 1.0); }

    };

};

#endif
