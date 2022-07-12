#include "error.h"
#include <iostream>
#include "types.h"

errors::errors(str msg) {
    m = msg;
}

s_ptr<errors> errors::new_error(str msg) {
    s_ptr<errors> instance(new errors(msg));
    return instance;
}

str errors::msg() {
    return m;
}

const char* errors::cmsg() {
    return m.c_str();
}
