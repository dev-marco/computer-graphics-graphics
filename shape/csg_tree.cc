#include "csg_tree.h"

namespace Shape {

    bool CSGTree::intersectLine (
        const Geometry::Line &line,
        float_max_t &t_min, float_max_t &t_max,
        bool get_info,
        Geometry::Vec<3> &normal_min, Geometry::Vec<3> &normal_max,
        bool &inside_min, bool &inside_max,
        Pigment::Color &color_min, Pigment::Color &color_max,
        Light::Material &material_min, Light::Material &material_max
    ) const {
        unsigned min_index, max_index;
        Geometry::Vec<3> shapes_normal[4];
        Pigment::Color shapes_color[4];
        Light::Material shapes_material[4];
        float_max_t shapes_inter[4];
        bool shapes_result[2], shapes_inside[4], global_result = false;

        shapes_result[0] = this->getFirst()->intersectLine(
            line,
            shapes_inter[0]   , shapes_inter[2],
            get_info,
            shapes_normal[0]  , shapes_normal[2],
            shapes_inside[0]  , shapes_inside[2],
            shapes_color[0]   , shapes_color[2],
            shapes_material[0], shapes_material[2]
        );

        if (shapes_result[0] || this->getOperation() != Type::SUBTRACTION) {

            shapes_result[1] = this->getSecond()->intersectLine(
                line,
                shapes_inter[1]   , shapes_inter[3],
                get_info,
                shapes_normal[1]  , shapes_normal[3],
                shapes_inside[1]  , shapes_inside[3],
                shapes_color[1]   , shapes_color[3],
                shapes_material[1], shapes_material[3]
            );

            if (shapes_result[0]) {
                if (shapes_result[1]) {
                    switch (this->getOperation()) {
                        case Type::UNION:
                            min_index = shapes_inter[0] < shapes_inter[1] ? 0 : 1;
                            max_index = shapes_inter[2] > shapes_inter[3] ? 2 : 3;
                            global_result = true;
                        break;
                        case Type::INTERSECTION:
                            min_index = shapes_inter[0] < shapes_inter[1] ? 1 : 0;
                            max_index = shapes_inter[2] > shapes_inter[3] ? 3 : 2;
                            global_result = shapes_inter[min_index] <= shapes_inter[max_index];
                        break;
                        case Type::SUBTRACTION:
                            if (shapes_inter[0] < shapes_inter[1]) {
                                min_index = 0;
                                max_index = shapes_inter[2] < shapes_inter[1] ? 2 : 1;
                                global_result = true;
                            } else if (shapes_inter[3] < shapes_inter[2]) {
                                if (shapes_inter[0] > shapes_inter[3]) {
                                    min_index = 0;
                                    max_index = 2;
                                } else {
                                    min_index = 3;
                                    max_index = 2;
                                }
                                global_result = true;
                            }
                    }
                } else if (this->getOperation() != Type::INTERSECTION) {
                    min_index = 0;
                    max_index = 2;
                    global_result = true;
                }
            } else if (shapes_result[1] && this->getOperation() == Type::UNION) {
                min_index = 1;
                max_index = 3;
                global_result = true;
            }
        }
        if (global_result) {
            t_min = shapes_inter[min_index];
            t_max = shapes_inter[max_index];

            normal_min.swap(shapes_normal[min_index]);
            normal_max.swap(shapes_normal[max_index]);

            inside_min = shapes_inside[min_index];
            inside_max = shapes_inside[max_index];

            color_min.swap(shapes_color[min_index]);
            color_max.swap(shapes_color[max_index]);

            material_min = shapes_material[min_index];
            material_max = shapes_material[max_index];
        }
        return global_result;
    }

};
