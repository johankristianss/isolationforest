#pragma once

#ifndef NODE_H
#define NODE_H

#include "types.h"

class node {
  private:
    node(int selected_feature, double split_value);

  public:
    static s_ptr<node> create(int select_feature, double split_value);

    int selected_feature;
    double split_value;
    s_ptr<node> left_node;
    s_ptr<node> right_node;
};

#endif
