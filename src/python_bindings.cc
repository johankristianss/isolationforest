#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "error.h"
#include "isolation_forest.h"
#include "isolation_tree.h"
#include "math.h"

PYBIND11_MODULE(iceml, m) {
    Eigen::initParallel();
    Eigen::setNbThreads(4);

    m.doc() = "iceml library";

    pybind11::class_<errors, s_ptr<errors>>(m, "errors").def("msg", &errors::msg);

    pybind11::class_<isolation_forest, s_ptr<isolation_forest>>(m, "isolation_forest")
        .def_static("create", &isolation_forest::create)
        .def("fit", &isolation_forest::fit)
        .def("expected_path_lengths", &isolation_forest::expected_path_lengths)
        .def("anom_score", &isolation_forest::anom_score)
        .def("anomalies", &isolation_forest::anomalies)
        .def("get_subsample", &isolation_forest::get_subsample);

    pybind11::class_<isolation_tree, s_ptr<isolation_tree>>(m, "isolation_tree")
        .def_static("create", &isolation_tree::create)
        .def("fit", &isolation_tree::fit)
        .def("path_lengths", &isolation_tree::path_lengths);
}
