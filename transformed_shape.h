#ifndef MODULE_SPATIAL_TRANSFORMED_SHAPE_H_
#define MODULE_SPATIAL_TRANSFORMED_SHAPE_H_

#include "../quaternion.h"
#include "shape.h"

namespace Spatial {

    class TransformedShape : public Shape {

        Shape *shape;
        std::array<float_max_t, 16> matrix, inv_matrix, inv_trans_matrix;
        Vec<3> pivot;

        void makeInverse(void);
        void makeTransposed(void);

        inline void updateMatrixes (void) { this->makeInverse(), this->makeTransposed(); }

        TransformedShape (
            const Shape *_shape, const Vec<3> &_pivot, const std::array<float_max_t, 16> &_matrix,
            const std::array<float_max_t, 16> &_inv_matrix, const std::array<float_max_t, 16> &_inv_trans_matrix
        ) :
            shape(_shape->clone()), matrix(_matrix), inv_matrix(_inv_matrix), inv_trans_matrix(_inv_trans_matrix), pivot(_pivot) {}

    public:

        static constexpr std::array<float_max_t, 16> identity = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };

        TransformedShape (const Shape *_shape, const Vec<3> &_pivot, const std::array<float_max_t, 16> &_matrix = identity) :
            shape(_shape->clone()), matrix(_matrix), pivot(_pivot) { this->updateMatrixes(); }

        void multiplyMatrix(const std::array<float_max_t, 16> &other);

        inline const Shape *getShape (void) const { return this->shape; }
        inline const Vec<3> &getPivot (void) const { return this->pivot; }
        inline const std::array<float_max_t, 16> &getMatrix (void) const { return this->matrix; }
        inline const std::array<float_max_t, 16> &getMatrixInverse (void) const { return this->inv_matrix; }
        inline const std::array<float_max_t, 16> &getMatrixInverseTransposed (void) const { return this->inv_trans_matrix; }

        void scale(float_max_t sx, float_max_t sy, float_max_t sz);
        void shear(float_max_t sxy, float_max_t sxz, float_max_t syx, float_max_t syz, float_max_t szx, float_max_t szy);
        void rotate(const Quaternion &quat);
        void translate(float_max_t tx, float_max_t ty, float_max_t tz);

        inline bool fit (void) const override { return shape->fit(); }

        const Shape *boundingVolume(void) const override;

        inline const char *getType (void) const override { return "transformed_shape"; }

        inline Shape *clone (void) const override { return new TransformedShape(
            this->getShape(), this->getPivot(), this->getMatrix(),
            this->getMatrixInverse(), this->getMatrixInverseTransposed()
        ); }

        bool intersectLine(const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const override;

    };
};

#endif
