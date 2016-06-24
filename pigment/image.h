#ifndef MODULE_GRAPHICS_PIGMENT_IMAGE_H_
#define MODULE_GRAPHICS_PIGMENT_IMAGE_H_

#include <vector>
#include "color.h"

namespace Graphics {

    class Image {

        std::vector<std::vector<Pigment::Color>> image;
        unsigned width, height;

    public:

        static Image readPPM(const std::string &file);

        Image(unsigned _width, unsigned _height, const Pigment::Color &color = Pigment::Color());

        inline unsigned getHeight (void) const { return this->height; }
        inline unsigned getWidth (void) const { return this->width; }

        void colorPixel(const std::array<unsigned, 2> &position, const Pigment::Color &color);
        inline void setPixel (const std::array<unsigned, 2> &position, const Pigment::Color &color) { this->image[position[1]][position[0]] = color; }
        void normalize(void);

        void writePPM(const std::string &file);
    };

};

#endif
