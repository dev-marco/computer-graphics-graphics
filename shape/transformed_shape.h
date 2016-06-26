#ifndef MODULE_GRAPHICS_SHAPE_TRANSFORMED_SHAPE_H_
#define MODULE_GRAPHICS_SHAPE_TRANSFORMED_SHAPE_H_

#include "../geometry/quaternion.h"
#include "shape.h"

namespace Shape {

    class TransformedShape : public Shape {

        Shape *shape;
        std::array<float_max_t, 16> matrix, inv_matrix, inv_trans_matrix;
        Geometry::Vec<3> pivot;

        void makeInverse(void);
        void makeTransposed(void);

        inline void updateMatrixes (void) { this->makeInverse(), this->makeTransposed(); }

        TransformedShape (
            const Shape *_shape, const Geometry::Vec<3> &_pivot,
            Pigment::Texture *_texture, Light::Surface *_surface,
            const std::array<float_max_t, 16> &_matrix,
            const std::array<float_max_t, 16> &_inv_matrix,
            const std::array<float_max_t, 16> &_inv_trans_matrix
        ) :
            Shape(_texture, _surface), shape(_shape->clone()), matrix(_matrix), inv_matrix(_inv_matrix), inv_trans_matrix(_inv_trans_matrix), pivot(_pivot) {}

    public:

        static constexpr std::array<float_max_t, 16> identity = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };

        TransformedShape (
            const Shape *_shape = nullptr,
            const Geometry::Vec<3> &_pivot = Geometry::Vec<3>::origin,
            Pigment::Texture *_texture = nullptr,
            Light::Surface *_surface = nullptr,
            const std::array<float_max_t, 16> &_matrix = identity
        ) :
            Shape(_texture, _surface), shape(_shape ? _shape->clone() : nullptr), matrix(_matrix), pivot(_pivot) { this->updateMatrixes(); }

        void multiplyMatrix(const std::array<float_max_t, 16> &other);

        inline const Shape *getShape (void) const { return this->shape; }
        inline const Geometry::Vec<3> &getPivot (void) const { return this->pivot; }
        inline const std::array<float_max_t, 16> &getMatrix (void) const { return this->matrix; }
        inline const std::array<float_max_t, 16> &getMatrixInverse (void) const { return this->inv_matrix; }
        inline const std::array<float_max_t, 16> &getMatrixInverseTransposed (void) const { return this->inv_trans_matrix; }

        inline void setPivot (const Geometry::Vec<3> &_pivot) { this->pivot = _pivot; }
        void setShape (const Shape *_shape);

        void scale(float_max_t sx, float_max_t sy, float_max_t sz);
        void shear(float_max_t sxy, float_max_t sxz, float_max_t syx, float_max_t syz, float_max_t szx, float_max_t szy);
        void rotate(const Geometry::Quaternion &quat);
        void translate(const Geometry::Vec<3> &vec);

        inline bool fit (void) const override { return shape->fit(); }

        const Shape *boundingVolume(void) const override;

        inline const char *getType (void) const override { return "transformed_shape"; }

        inline Shape *clone (void) const override { return new TransformedShape(
            this->getShape(), this->getPivot(),
            this->getTexture(), this->getSurface(),
            this->getMatrix(), this->getMatrixInverse(),
            this->getMatrixInverseTransposed()
        ); }

        bool intersectLine (
            const Geometry::Line &line,
            Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
            Pigment::Color &color_min, Pigment::Color &color_max,
            Light::Material &material_min, Light::Material &material_max,
            float_max_t &t_min, float_max_t &t_max,
            bool fix_normals = true
        ) const override;

    };
};

#endif
