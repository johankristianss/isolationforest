#include "isolation_forest.h"
#include <random>
#include "error.h"
#include "types.h"

isolation_forest::isolation_forest(matrix data,
                                   int max_depth,
                                   int number_of_trees,
                                   bool subsampling,
                                   int subsample_size)
    : data(data),
      max_depth(max_depth),
      number_of_trees(number_of_trees),
      subsampling(subsampling),
      subsample_size(subsample_size) {
    for (int i = 0; i < this->number_of_trees; i++) {
        this->trees.push_back(isolation_tree::create());

        if (this->subsampling) {
            matrix subsample(subsample_size, data.cols());
            this->subsamples.push_back(subsample);
        }
    }

    if (this->subsampling) {
        this->create_subsamples();
    }
}

pair<s_ptr<isolation_forest>, error> isolation_forest::create(const matrix data,
                                                              const int max_depth,
                                                              const int number_of_trees,
                                                              bool subsampling,
                                                              int subsample_size) {
    if (subsampling) {
        if (number_of_trees * subsample_size > data.rows()) {
            return {nullptr, errors::new_error("too few data samples for subsampling")};
        }
    }

    s_ptr<isolation_forest> instance(
        new isolation_forest(data, max_depth, number_of_trees, subsampling, subsample_size));
    return {instance, no_error};
}

void isolation_forest::create_subsamples() {
    for (int i = 0; i < this->number_of_trees; i++) {
        for (int j = 0; j < this->subsample_size; j++) {
            int row_index = this->random_row();
            auto row = this->row(row_index);
            // this->append_row(row, this->subsamples.at(i));
            this->subsamples.at(i).row(j) = row;
            // this->remove_row(row_index);
        }
    }
}

error isolation_forest::fit() {
    for (int i = 0; i < this->trees.size(); i++) {
#ifdef PRINT
        std::cout << "-> training tree " << i << std::endl;
#endif
        if (this->subsampling) {
            auto err = this->trees.at(i)->fit(this->subsamples.at(i), this->max_depth);
            if (err != nullptr) {
                return err;
            }
        } else {
            auto err = this->trees.at(i)->fit(this->data, this->max_depth);
            if (err != nullptr) {
                return err;
            }
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

matrix isolation_forest::row(unsigned int row) {
    return this->data.row(row);
}

int isolation_forest::random_row() {
    // TODO: is it safe to call the functions below many times?
    std::uniform_real_distribution<> dis(0, this->data.rows());
    std::random_device rd;
    std::mt19937 gen(rd());
    return dis(gen);
}

void isolation_forest::remove_row(unsigned int row) {
    unsigned int num_rows = this->data.rows() - 1;
    unsigned int num_cols = this->data.cols();

    if (num_rows == 0) {
        return;
    }

    if (row <= num_rows) {
        this->data.block(row, 0, num_rows - row, num_cols) = this->data.block(row + 1, 0, num_rows - row, num_cols);
        this->data.conservativeResize(num_rows, num_cols);
    }
}

void isolation_forest::append_row(matrix row, matrix& target) {
    target.conservativeResize(target.rows() + 1, target.cols());
    target.row(target.rows() - 1) = row;
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

matrix& isolation_forest::get_data() {
    return this->data;
}

matrix& isolation_forest::get_subsample(int index) {
    return this->subsamples.at(index);
}
