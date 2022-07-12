#pragma once

#ifndef ISOLATION_FOREST_H
#define ISOLATION_FOREST_H

#include "error.h"
#include "isolation_tree.h"
#include "types.h"

class isolation_forest {
  private:
    isolation_forest(matrix data, int max_depth, int number_of_trees, bool subsampling, int subsample_size);
    vec<s_ptr<isolation_tree>> trees;
    vec<matrix> subsamples;
    matrix data;
    int max_depth;
    int number_of_trees;
    bool subsampling;
    int subsample_size;

  public:
    static pair<s_ptr<isolation_forest>, error> create(matrix data,
                                                       int max_depth,
                                                       int number_of_trees,
                                                       bool subsampling,
                                                       int subsample_size);
    void create_subsamples();
    error fit();
    matrix expected_path_lengths(const matrix& data);
    matrix row(unsigned int row);
    int random_row();
    void remove_row(unsigned int row);
    void append_row(matrix row, matrix& target);
    matrix anom_score(const matrix& data);
    matrix calc_anom_score(const matrix& data, bool use_threshold, double threshold);
    matrix anomalies(const matrix& data, double threshold);
    matrix& get_data();
    matrix& get_subsample(int index);
};

#endif
