#ifndef MODULE_GRAPHICS_LIGHT_MATERIAL_H_
#define MODULE_GRAPHICS_LIGHT_MATERIAL_H_

#include "../geometry/defaults.h"
#include "../geometry/vec.h"

namespace Light {

    class Material {

        float_max_t ambient, diffuse, specular, alpha, reflect, transmit, ior;
        Geometry::Vec<3> normal;

    public:

        Material () {}

        Material (
            float_max_t _ambient, float_max_t _diffuse, float_max_t _specular, float_max_t _alpha,
            float_max_t _reflect, float_max_t _transmit, float_max_t _ior,
            const Geometry::Vec<3> &_normal = Geometry::Vec<3>::zero
        ) :
            ambient(_ambient), diffuse(_diffuse), specular(_specular), alpha(_alpha), reflect(_reflect), transmit(_transmit), ior(_ior), normal(_normal) {};

        Material (
            const std::array<float_max_t, 1> &_ambient, const std::array<float_max_t, 1> &_diffuse,
            const std::array<float_max_t, 1> &_specular, const std::array<float_max_t, 1> &_alpha,
            const std::array<float_max_t, 1> &_reflect, const std::array<float_max_t, 1> &_transmit,
            const std::array<float_max_t, 1> &_ior, const std::array<float_max_t, 3> &_normal = { 0.0, 0.0, 0.0 }
        ) :
            ambient(_ambient[0]), diffuse(_diffuse[0]), specular(_specular[0]), alpha(_alpha[0]), reflect(_reflect[0]), transmit(_transmit[0]), ior(_ior[0]), normal(_normal) {};

        inline const float_max_t &getAmbient (void) const { return this->ambient; }
        inline const float_max_t &getDiffuse (void) const { return this->diffuse; }
        inline const float_max_t &getSpecular (void) const { return this->specular; }
        inline const float_max_t &getAlpha (void) const { return this->alpha; }
        inline const float_max_t &getReflect (void) const { return this->reflect; }
        inline const float_max_t &getTransmit (void) const { return this->transmit; }
        inline const float_max_t &getIOR (void) const { return this->ior; }

        inline void setAmbient (const float_max_t &_ambient) { this->ambient = _ambient; }
        inline void setDiffuse (const float_max_t &_diffuse) { this->diffuse = _diffuse; }
        inline void setSpecular (const float_max_t &_specular) { this->specular = _specular; }
        inline void setAlpha (const float_max_t &_alpha) { this->alpha = _alpha; }
        inline void setReflect (const float_max_t &_reflect) { this->reflect = _reflect; }
        inline void setTransmit (const float_max_t &_transmit) { this->transmit = _transmit; }
        inline void setIOR (const float_max_t &_ior) { this->ior = _ior; }

    };

}

#endif
