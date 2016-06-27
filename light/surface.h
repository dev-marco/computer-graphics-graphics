#ifndef MODULE_GRAPHICS_LIGHT_SURFACE_H_
#define MODULE_GRAPHICS_LIGHT_SURFACE_H_

#include "../geometry/defaults.h"
#include "../geometry/vec.h"
#include "../geometry/plane.h"
#include "material.h"
#include "property.h"

namespace Light {

    class Surface {

        Property<1> *ambient, *diffuse, *specular, *alpha, *reflect, *transmit, *ior;
        Property<3> *normal;
        bool need_param;

    public:

        Surface (
            Property<1> *_ambient,
            Property<1> *_diffuse,
            Property<1> *_specular,
            Property<1> *_alpha,
            Property<1> *_reflect,
            Property<1> *_transmit,
            Property<1> *_ior,
            Property<3> *_normal
        ) :
            ambient(_ambient), diffuse(_diffuse), specular(_specular), alpha(_alpha), reflect(_reflect), transmit(_transmit), ior(_ior), normal(_normal) {
                need_param = _ambient->needParameter() || _diffuse->needParameter()
                || _specular->needParameter() || _alpha->needParameter() || _reflect->needParameter()
                || _transmit->needParameter() || _ior->needParameter() || _normal->needParameter();
            }

        Material at (const Geometry::Vec<2> &param, const Geometry::Vec<3> &point) const {
            return Material(
                ambient->at(param, point),
                diffuse->at(param, point),
                specular->at(param, point),
                alpha->at(param, point),
                reflect->at(param, point),
                transmit->at(param, point),
                ior->at(param, point),
                normal->at(param, point)
            );
        }

        inline bool needParameter (void) const { return this->need_param; }

    };

};

#endif
