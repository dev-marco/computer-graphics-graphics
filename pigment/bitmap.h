#ifndef MODULE_GRAPHICS_PIGMENT_BITMAP_H_
#define MODULE_GRAPHICS_PIGMENT_BITMAP_H_

#include <opencv2/opencv.hpp>
#include "../geometry/vec.h"
#include "texture.h"

namespace Pigment {

    class Bitmap : public Texture {

        cv::Mat image;

    public:
        Bitmap (
            const std::string &file,
            const float_max_t &_s_size = 1.0,
            const float_max_t &_t_size = 1.0,
            const float_max_t &_s_offset = 0.0,
            const float_max_t &_t_offset = 0.0
        ) :
            Texture(_s_size, _t_size, _s_offset, _t_offset), image(cv::imread(file)) {}

        const cv::Mat &getImage (void) const { return this->image; }

        inline Color at (const Geometry::Vec<2> &param, const Geometry::Vec<3> &point) const override {
            const cv::Mat &image = this->getImage();
            const Geometry::Vec<2> &param_norm = {
                param[0] * this->getInverseSSize() + this->getSOffset(),
                param[1] * this->getInverseTSize() + this->getTOffset()
            };
            return image.at<cv::Vec3b>(
                Geometry::fract(param_norm[1]) * (image.rows - 1),
                Geometry::fract(param_norm[0]) * (image.cols - 1)
            );
        }

    };

};

#endif
