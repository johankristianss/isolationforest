#pragma once

#ifndef TEST_H
#define TEST_H

#include <Eigen/Dense>
#include "error.h"

const double precision = 0.01;

bool has_error(error err);
bool is_equal(const matrix& a, const matrix& b);
bool is_within(float a, float b, float threshold);

#endif
