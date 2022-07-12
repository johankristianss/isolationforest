#pragma once

#ifndef ISOLATION_FOREST_H
#define ISOLATION_FOREST_H

#include "error.h"
#include "isolation_tree.h"
#include "types.h"

class isolation_forest {
  private:
    isolation_forest(const matrix data, const int max_depth, const int number_of_trees);
    vec<s_ptr<isolation_tree>> trees;
    const matrix data;
    int max_depth;
    int number_of_trees;

  public:
    static s_ptr<isolation_forest> create(const matrix data, const int max_depth, const int number_of_trees);
    error fit();
    matrix expected_path_lengths(const matrix& data);
    matrix anom_score(const matrix& data);
    matrix calc_anom_score(const matrix& data, bool use_threshold, double threshold);
    matrix anomalies(const matrix& data, double threshold);
};

#endif
