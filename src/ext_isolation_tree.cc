#include "ext_isolation_tree.h"
#include <random>
#include "error.h"
#include "types.h"

ext_isolation_tree::ext_isolation_tree() {
    srand(time(NULL));
}

s_ptr<ext_isolation_tree> ext_isolation_tree::create() {
    s_ptr<ext_isolation_tree> instance(new ext_isolation_tree);
    return instance;
}

const pair<matrix, matrix> ext_isolation_tree::split(const matrix& data,
                                                     const int selected_feature,
                                                     const double split_value) {
}
