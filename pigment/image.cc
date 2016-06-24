#include <fstream>
#include "image.h"

namespace Graphics {

    Image::Image (unsigned _width, unsigned _height, const Pigment::Color &color) :
        width(_width), height(_height)
    {
        this->image.resize(_height);
        for (unsigned i = 0; i < _height; ++i) {
            this->image[i].resize(_width);
            std::fill(std::begin(this->image[i]), std::end(this->image[i]), color);
        }
    }

    void Image::colorPixel (const std::array<unsigned, 2> &position, const Pigment::Color &color) {
        if (
            position[0] >= 0 && position[0] < this->getWidth() &&
            position[1] >= 0 && position[1] < this->getHeight()
        ) {
            this->setPixel(position, color);
        }
    }

    void Image::normalize (void) {
        float_max_t max_val = 0.0;
        for (unsigned y = 0, height = this->getHeight(), width = this->getWidth(); y < height; ++y) {
            for (unsigned x = 0; x < width; ++x) {
                const Pigment::Color &pixel = this->image[y][x];
                if (pixel.red() > max_val) {
                    max_val = pixel.red();
                }
                if (pixel.green() > max_val) {
                    max_val = pixel.green();
                }
                if (pixel.blue() > max_val) {
                    max_val = pixel.blue();
                }
            }
        }
        if (max_val > 0.0) {
            for (unsigned y = 0, height = this->getHeight(), width = this->getWidth(); y < height; ++y) {
                for (unsigned x = 0; x < width; ++x) {
                    this->image[y][x] /= max_val;
                }
            }
        }
    }

    void Image::writePPM (const std::string &file) {
        std::ofstream out(file);
        out << "P3" << std::endl << this->getWidth() << ' ' << this->getHeight() << std::endl << "255" << std::endl;
        for (const auto &line : image) {
            for (const auto &color : line) {
                const unsigned
                    R = std::min(255.0, std::max(0.0, color.red() * 255.0)),
                    G = std::min(255.0, std::max(0.0, color.green() * 255.0)),
                    B = std::min(255.0, std::max(0.0, color.blue() * 255.0));
                out << R << ' ' << G << ' ' << B << ' ';
            }
            out << std::endl;
        }
        out.close();
    }
};
