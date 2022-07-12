#include "node.h"
#include "types.h"

node::node(int selected_feature, double split_value)
    : selected_feature(selected_feature), split_value(split_value), left_node(nullptr), right_node(nullptr) {
}

s_ptr<node> node::create(int selected_feature, double split_value) {
    s_ptr<node> instance(new node(selected_feature, split_value));
    return instance;
}
