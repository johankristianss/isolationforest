#include "isolation_forest.h"
#include "types.h"

isolation_forest::isolation_forest(const matrix data, const int max_depth, const int number_of_trees)
    : data(data), max_depth(max_depth), number_of_trees(number_of_trees) {
}

s_ptr<isolation_forest> isolation_forest::create(const matrix data, const int max_depth, const int number_of_trees) {
    s_ptr<isolation_forest> instance(new isolation_forest(data, max_depth, number_of_trees));
    return instance;
}

error isolation_forest::fit() {
    for (int i = 0; i < this->number_of_trees; i++) {
        this->trees.push_back(isolation_tree::create());
    }

    for (int i = 0; i < this->trees.size(); i++) {
        auto err = this->trees.at(i)->fit(this->data, this->max_depth);
        if (err != nullptr) {
            return err;
        }
    }

    return no_error;
}

matrix isolation_forest::expected_path_lengths(const matrix& data) {
    matrix expected_path_lengths(data.rows(), 1);
    expected_path_lengths.setZero();

    for (int i = 0; i < this->trees.size(); i++) {
        auto path_lengths = this->trees.at(i)->path_lengths(data);
        expected_path_lengths = expected_path_lengths + path_lengths;
    }

    return expected_path_lengths / this->trees.size();
}

matrix isolation_forest::anom_score(const matrix& data) {
    // c(n) = 2H(n − 1) − (2(n − 1)/n)
    // H(i) is the harmonic number and it can be estimated by ln(i) + 0.5772156649 (Euler’s constant)
    double euler_constant = 0.5772156649;
    int n = data.rows();
    double c_factor = 2.0 * (std::log(n - 1) + euler_constant) - (2.0 * (n - 1.) / (n * 1.0));
    auto anom_score = -(expected_path_lengths(data) / c_factor);
    auto result = anom_score.array().pow(2);

    return result;
}

matrix isolation_forest::anomalies(const matrix& data, double threshold) {
    auto anom_score = this->anom_score(data);

    for (int i = 0; i < anom_score.rows(); i++) {
        if (anom_score(i) <= threshold) {
            anom_score(i) = 1.0;
        } else {
            anom_score(i) = 0.0;
        }
    }

    return anom_score;
}
