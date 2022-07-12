#include "isolation_tree.h"
#include <random>
#include "error.h"
#include "types.h"

isolation_tree::isolation_tree() {
    srand(time(NULL));
}

s_ptr<isolation_tree> isolation_tree::create() {
    s_ptr<isolation_tree> instance(new isolation_tree);
    return instance;
}

error isolation_tree::fit(const matrix& data, const int max_depth) {
    if (data.cols() == 0) {
        return errors::new_error("invalid data matrix, zero cols");
    }

    if (data.rows() == 0) {
        return errors::new_error("invalid data matrix, zero rows");
    }

    this->root_node = node::create(0, 0.0);

    build_tree(data, root_node, 0, max_depth);

    return no_error;
}

void isolation_tree::build_tree(const matrix& data, s_ptr<node> node, const int current_depth, const int max_depth) {
    auto selected_feature = this->select_feature(data);
    auto split_value = this->select_split_value(data, selected_feature);
    auto [above, below] = this->split(data, selected_feature, split_value);
    auto left_node = node::create(selected_feature, split_value);
    auto right_node = node::create(selected_feature, split_value);

    node->selected_feature = selected_feature;
    node->split_value = split_value;
    node->left_node = left_node;
    node->right_node = right_node;

    if (above.rows() == 1 || current_depth == max_depth) {
        return;
    } else {
        build_tree(above, left_node, current_depth + 1, max_depth);
    }

    if (below.rows() == 1 || current_depth == max_depth) {
        return;
    } else {
        build_tree(below, right_node, current_depth + 1, max_depth);
    }
}

matrix isolation_tree::path_lengths(const matrix& data) {
    matrix path_lengths(data.rows(), 1);
    path_lengths.setZero();
    int path_length;
    for (int i = 0; i < data.rows(); i++) {
        auto row = data.row(i);
        path_length = path_length_recursively(this->root_node, row, 1);
        //        std::cout << path_length << std::endl;
        path_lengths(i) = path_length;
    }

    return path_lengths;
}

int isolation_tree::path_length_recursively(s_ptr<node> node, const matrix& data, const int counter) {
    if (data(0, node->selected_feature) < node->split_value) {
        if (node->left_node != nullptr) {
            return path_length_recursively(node->left_node, data, counter + 1);
        }
    } else {
        if (node->right_node != nullptr) {
            return path_length_recursively(node->right_node, data, counter + 1);
        }
    }

    return counter;
}

void isolation_tree::print_tree() {
    print_tree_recursively(this->root_node);
}

void isolation_tree::print_tree_recursively(s_ptr<node> node) {
    std::cout << "(" << node->selected_feature << ", " << node->split_value << ")";

    if (node->left_node != nullptr) {
        print_tree_recursively(node->left_node);
    }

    if (node->right_node != nullptr) {
        print_tree_recursively(node->right_node);
    }
}

int isolation_tree::select_feature(const matrix& data) {
    return rand() % (data.cols());
}

double isolation_tree::select_split_value(const matrix& data, int feature) {
    // note that the block abstraction has zero runtime cost
    // see https://eigen.tuxfamily.org/dox/group__TutorialBlockOperations.html for more info
    auto col = data.block(0, feature, data.rows(), 1);

    double minValue = col.minCoeff();
    double maxValue = col.maxCoeff();

    // TODO: is it safe to call the functions below many times?
    std::uniform_real_distribution<> dis(minValue, maxValue);
    std::random_device rd;
    std::mt19937 gen(rd());
    return dis(gen);
}

const pair<matrix, matrix> isolation_tree::split(const matrix& data,
                                                 const int selected_feature,
                                                 const double split_value) {
    matrix above(0, data.cols());
    matrix below(0, data.cols());

    for (int i = 0; i < data.rows(); i++) {
        auto row = data.block(i, 0, 1, data.cols());

        if (data(i, selected_feature) < split_value) {
            above.conservativeResize(above.rows() + 1, data.cols());
            above.row(above.rows() - 1) << row;
        } else {
            below.conservativeResize(below.rows() + 1, data.cols());
            below.row(below.rows() - 1) << row;
        }
    }

    return {above, below};
}
