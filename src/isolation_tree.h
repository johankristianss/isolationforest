#pragma once

#ifndef ISOLATION_TREE_H
#define ISOLATION_TREE_H

#include "error.h"
#include "node.h"
#include "types.h"

class isolation_tree {
  private:
    isolation_tree();
    s_ptr<node> root_node;

  public:
    static s_ptr<isolation_tree> create();
    error fit(const matrix& data, const int max_depth);
    void build_tree(const matrix& data, s_ptr<node> node, const int current_depth, const int max_depth);
    void print_tree();
    void print_tree_recursively(s_ptr<node> node);
    matrix path_lengths(const matrix& data);
    int path_length_recursively(s_ptr<node> node, const matrix& data, const int counter);
    int select_feature(const matrix& data);
    double select_split_value(const matrix& data, int feature);
    const pair<matrix, matrix> split(const matrix& data, const int select_feature, const double split_value);
};

#endif
