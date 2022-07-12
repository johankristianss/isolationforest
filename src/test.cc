#include "test.h"
#include "error.h"
#include "math.h"

bool has_error(error err) {
    if (err) {
        return true;
    }

    return false;
}

bool is_equal(const matrix& a, const matrix& b) {
    if (((a - b).norm() > precision) == 0) {
        return true;
    }
    return false;
}

bool is_within(float a, float b, float threshold) {
    return std::abs(a - b) <= threshold;
}
