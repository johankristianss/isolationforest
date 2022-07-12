#ifndef TYPES_H
#define TYPES_H

#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <unordered_map>
#include <vector>

template <typename t>
using vec = std::vector<t>;

template <typename... Args>
using arr = std::array<Args...>;

template <typename t>
using list = std::list<t>;

template <typename... Args>
using tup = std::tuple<Args...>;

template <typename t>
using s_ptr = std::shared_ptr<t>;

template <typename... Args>
using pair = std::pair<Args...>;

using str = std::string;

template <typename... Args>
using map = std::map<Args...>;

template <typename... Args>
using hash = std::unordered_map<Args...>;

using matrix = Eigen::MatrixXf;

#endif
