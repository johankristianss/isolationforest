#include "../src/isolation_forest.h"
#include "../src/test.h"

#include "gtest/gtest.h"

TEST(isolation_forest, create) {}

TEST(isolation_forest, expected_path_lengths) {
  matrix data(23, 2);
  // clang-format off
  data << -0.301169,   1.38177,
           0.540302,   0.841471,
          -0.539944,  -0.899763,
          -2.37607,   -1.04806,
          -1.43063,   -1.26289,
           0.224402,  -1.78937,
          -0.503317,  -0.177942,
          -0.261555,   0.0580515,
          -0.14588,   -0.904594,
          -0.0432764, -0.116452,
           0.378512,  -1.51801,
          -0.148816,   0.520947,
          -0.961607,  -0.716857,
          -0.129833,   1.09857,
           0.0730111,  0.978524,
          -1.41921,    1.13591,
           0.522388,   0.984212,
           0.642612,   1.01213,
           1.14996,   -0.547578,
           0.0629548, -1.99983,
          -1.01161,   -2.71711,
          -1.24093,    0.210725,
           40.4,       40.4;  // <- Anomaly
  // clang-format on

  auto iforest = isolation_forest::create(data, 300, 10);
  iforest->fit();
  auto expected_path_lengths = iforest->expected_path_lengths(data);
  // TODO
}

TEST(isolation_forest, c_factor) {
  matrix data(23, 2);
  // clang-format off
  data << -0.301169,   1.38177,
           0.540302,   0.841471,
          -0.539944,  -0.899763,
          -2.37607,   -1.04806,
          -1.43063,   -1.26289,
           0.224402,  -1.78937,
          -0.503317,  -0.177942,
          -0.261555,   0.0580515,
          -0.14588,   -0.904594,
          -0.0432764, -0.116452,
           0.378512,  -1.51801,
          -0.148816,   0.520947,
          -0.961607,  -0.716857,
          -0.129833,   1.09857,
           0.0730111,  0.978524,
          -1.41921,    1.13591,
           0.522388,   0.984212,
           0.642612,   1.01213,
           1.14996,   -0.547578,
           0.0629548, -1.99983,
          -1.01161,   -2.71711,
          -1.24093,    0.210725,
           40.4,       40.4;  // <- Anomaly
  // clang-format on

  auto iforest = isolation_forest::create(data, 300, 10);
  iforest->fit();
  auto anom_score = iforest->anom_score(data);
  //  std::cout << anom_score << std::endl;
  // TODO
}

TEST(isolation_forest, anomalies) {
  matrix data(23, 2);
  // clang-format off
  data << -0.301169,   1.38177,
           0.540302,   0.841471,
          -0.539944,  -0.899763,
          -2.37607,   -1.04806,
          -1.43063,   -1.26289,
           0.224402,  -1.78937,
          -0.503317,  -0.177942,
          -0.261555,   0.0580515,
          -0.14588,   -0.904594,
          -0.0432764, -0.116452,
           0.378512,  -1.51801,
          -0.148816,   0.520947,
          -0.961607,  -0.716857,
          -0.129833,   1.09857,
           0.0730111,  0.978524,
          -1.41921,    1.13591,
           0.522388,   0.984212,
           0.642612,   1.01213,
           1.14996,   -0.547578,
           0.0629548, -1.99983,
          -1.01161,   -2.71711,
          -1.24093,    0.210725,
           40.4,       40.4;  // <- Anomaly
  // clang-format on

  auto iforest = isolation_forest::create(data, 300, 10);
  iforest->fit();

  auto anomalies = iforest->anomalies(data, 0.2);
  // std::cout << anomalies << std::endl;
  // TODO
}
