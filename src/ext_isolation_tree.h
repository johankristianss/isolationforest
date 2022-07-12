#pragma once

#ifndef EXT_ISOLATION_TREE_H
#define EXT_ISOLATION_TREE_H

#include "error.h"
#include "node.h"
#include "types.h"

class ext_isolation_tree {
  private:
    ext_isolation_tree();
    s_ptr<node> root_node;

  public:
    static s_ptr<ext_isolation_tree> create();
    const pair<matrix, matrix> split(const matrix& data, const int select_feature, const double split_value);
};

#endif
