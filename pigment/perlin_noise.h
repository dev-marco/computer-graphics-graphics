#ifndef MODULE_GRAPHICS_PIGMENT_PERLIN_NOISE_H_
#define MODULE_GRAPHICS_PIGMENT_PERLIN_NOISE_H_

#include <algorithm>
#include <chrono>
#include <random>
#include "../geometry/defaults.h"

namespace Pigment {

    class PerlinNoise {

        unsigned char p[512] = { 151,160,137,91,90,15,
            131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
            190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
            88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
            77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
            102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
            135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
            5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
            223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
            129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
            251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
            49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,151,
            160,137,91, 90, 15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,
            99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
            35,11,32,57,177,33,88,237,149,56,87,174, 20,125,136,171,168, 68,175, 74,165,
            71,134,139,48,27,166,77,146,158,231, 83,111,229,122, 60,211,133,230,220,105,
            92,41,55,46,245,40,244,102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,
            208, 89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,
            52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,
            16,58,17,182,189, 28, 42,223,183,170,213,119,248,152, 2, 44,154,163, 70,221,
            153,101,155,167, 43,172,9,129,22,39,253, 19, 98,108,110, 79,113,224,232,178,
            185, 112,104,218,246,97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
            81,51,145,235,249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,
            115,121,50,45,127, 4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,
            195,78,66,215,61,156,180
        };

        inline static float_max_t fade (const float_max_t &t) { return t * t * t * (t * (t * 6 - 15) + 10); }

        inline static float_max_t lerp (const float_max_t &t, const float_max_t &a, const float_max_t &b) { return a + t * (b - a); }

        inline static float_max_t grad (const unsigned &hash, const float_max_t &x, const float_max_t &y, const float_max_t &z) {
            const unsigned h = hash & 15;
            const float_max_t
                u = (h < 8) ? x : y,
                v = (h < 4) ? y : ((h == 12 || h == 14) ? x : z);

           return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
        }

    public:

        void shuffle (unsigned seed) {
            std::mt19937 gen(seed);
            unsigned char *end = this->p + 255;
            std::iota(this->p, end, 0);
            std::shuffle(this->p, end, gen);
            std::copy_n(this->p, 255, end);
        }

        void shuffle (void) {
            shuffle(std::chrono::system_clock::now().time_since_epoch().count() & 0xFFFFFFFF);
        }

        PerlinNoise () {}

        PerlinNoise (unsigned seed) { this->shuffle(seed); }

        float_max_t at (const float_max_t &x, const float_max_t &y = 0.0, const float_max_t &z = 0.0) const {
            const unsigned
                x_floor = std::floor(x),
                y_floor = std::floor(y),
                z_floor = std::floor(z),
                X = x_floor & 255,
                Y = y_floor & 255,
                Z = z_floor & 255;

            const float_max_t
                fract_x = x - x_floor,
                fract_y = y - y_floor,
                fract_z = z - z_floor,
                fract_x_1 = fract_x - 1.0,
                fract_y_1 = fract_y - 1.0,
                fract_z_1 = fract_z - 1.0,
                u = fade(fract_x),
                v = fade(fract_y),
                w = fade(fract_z);

            const unsigned char
                A  = p[X] + Y,
                AA = p[A] + Z, AB = p[A + 1] + Z,
                B  = p[X + 1] + Y,
                BA = p[B] + Z, BB = p[B + 1] + Z;

            return lerp(w,
                lerp(v,
                    lerp(u, grad(p[AA], fract_x, fract_y, fract_z),
                        grad(p[BA], fract_x_1, fract_y  , fract_z)
                    ),
                    lerp(u, grad(p[AB], fract_x, fract_y_1, fract_z),
                        grad(p[BB], fract_x_1, fract_y_1, fract_z)
                    )
                ),
                lerp(v,
                    lerp(u, grad(p[AA + 1], fract_x, fract_y, fract_z_1),
                        grad(p[BA + 1], fract_x_1, fract_y, fract_z_1)
                    ),
                    lerp(u, grad(p[AB + 1], fract_x, fract_y_1, fract_z_1),
                        grad(p[BB + 1], fract_x_1, fract_y_1, fract_z_1)
                    )
                )
            );
        }

    };
}

#endif
