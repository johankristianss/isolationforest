#include "../src/isolation_tree.h"
#include "../src/test.h"

#include "gtest/gtest.h"

TEST(isolation_tree, select_feature) {
  int first_feature = 0;
  int second_feature = 0;
  int third_feature = 0;
  int selected_feature;

  auto itree = isolation_tree::create();

  matrix data1(5, 1);
  // clang-format off
  data1 << 0.1,
           1.2,
           2.3,
           3.4,
           4.5;
  // clang-format on

  for (int i = 0; i < 1000; i++) {
    selected_feature = itree->select_feature(data1);
    if (selected_feature == 0) {
      first_feature++;
    } else if (selected_feature == 1) {
      second_feature++;
    } else if (selected_feature == 2) {
      third_feature++;
    }
  }

  EXPECT_TRUE(first_feature > 200);
  EXPECT_TRUE(second_feature == 0);
  EXPECT_TRUE(third_feature == 0);

  first_feature = 0;
  second_feature = 0;
  third_feature = 0;

  matrix data2(5, 2);
  // clang-format off
  data2 << 0.1, 10.1,
           1.2, 11.2,
           2.3, 12.3,
           3.4, 13.4,
           4.5, 14.5;
  // clang-format on

  for (int i = 0; i < 1000; i++) {
    selected_feature = itree->select_feature(data2);
    if (selected_feature == 0) {
      first_feature++;
    } else if (selected_feature == 1) {
      second_feature++;
    } else if (selected_feature == 2) {
      third_feature++;
    }
  }

  EXPECT_TRUE(first_feature > 200);
  EXPECT_TRUE(second_feature > 200);
  EXPECT_TRUE(third_feature == 0);

  first_feature = 0;
  second_feature = 0;
  third_feature = 0;

  matrix data3(5, 3);
  // clang-format off
  data3 << 0.1, 10.1, 20.1,
           1.2, 11.2, 21.2,
           2.3, 12.3, 22.3,
           3.4, 13.4, 23.4,
           4.5, 14.5, 34.5;
  // clang-format on

  for (int i = 0; i < 1000; i++) {
    selected_feature = itree->select_feature(data3);
    if (selected_feature == 0) {
      first_feature++;
    } else if (selected_feature == 1) {
      second_feature++;
    } else if (selected_feature == 2) {
      third_feature++;
    }
  }

  EXPECT_TRUE(first_feature > 200);
  EXPECT_TRUE(second_feature > 200);
  EXPECT_TRUE(third_feature > 200);
}

TEST(isolation_tree, select_split_value) {
  matrix data(10, 3);
  // clang-format off
  data << 0.0,  11.0, 1.0, 
          2.0,  12.0, 1.1,
          3.0,  13.0, 1.6,
          4.0,  14.0, 1.0,
          5.0,  15.0, 1.0,
          6.0,  16.0, 1.0,
          7.0,  17.0, 1.0,
          8.0,  18.0, 1.0,
          9.0,  19.0, 1.0,
          10.0, 2000.0, 1.0;
  // clang-format on

  auto itree = isolation_tree::create();

  double split_value_sum = 0.0;
  int runs = 10000;

  split_value_sum = 0.0;
  for (int i = 0; i < runs; i++) {
    split_value_sum += itree->select_split_value(data, 0);
  }
  double split_value_mean = split_value_sum / runs;
  EXPECT_TRUE(split_value_mean > 4.5 && split_value_mean < 5.5);

  split_value_sum = 0.0;
  for (int i = 0; i < runs; i++) {
    split_value_sum += itree->select_split_value(data, 1);
  }
  split_value_mean = split_value_sum / runs;

  split_value_sum = 0.0;
  EXPECT_TRUE(split_value_mean > 900 && split_value_mean < 1100);
  for (int i = 0; i < runs; i++) {
    split_value_sum += itree->select_split_value(data, 2);
  }
  split_value_mean = split_value_sum / runs;
  EXPECT_TRUE(split_value_mean > 1.2 && split_value_mean < 1.4);
}

TEST(isolation_tree, split_test_1) {
  matrix data(4, 3);
  // clang-format off
  data << 0.0,  11.0,   1.0, 
          8.0,  18.0,   1.0,
          9.0,  19.0,   1.0,
          10.0, 2000.0, 1.0;
  // clang-format on

  auto itree = isolation_tree::create();
  auto [above, below] = itree->split(data, 0, 0.1);

  matrix expected_above(1, 3);
  // clang-format off
  expected_above << 0.0, 11.0, 1.0;
  // clang-format on

  EXPECT_TRUE(is_equal(above, expected_above));

  matrix expected_above2(3, 3);
  // clang-format off
  expected_above2 <<  8.0, 18.0, 1.0,
                      9.0, 19.0, 1.0,
                     10.0, 2000, 1.0;
  // clang-format on

  EXPECT_TRUE(is_equal(below, expected_above2));
}

TEST(isolation_tree, split_test_2) {
  matrix data(4, 3);
  // clang-format off
  data << 0.0,  11.0,   1.0, 
          8.0,  18.0,   1.0,
          9.0,  19.0,   1.0,
          10.0, 2000.0, 1.0;
  // clang-format on

  auto itree = isolation_tree::create();
  auto [above, below] = itree->split(data, 1, 20.0);

  matrix expected_above(3, 3);
  // clang-format off
  expected_above <<  0.0, 11.0, 1.0,
                     8.0, 18.0, 1.0,
                     9.0, 19.0, 1.0;
  // clang-format on

  EXPECT_TRUE(is_equal(above, expected_above));

  matrix expected_above2(1, 3);
  // clang-format off
  expected_above2 <<  10.0, 2000.0, 1.0;
  // clang-format on

  EXPECT_TRUE(is_equal(below, expected_above2));
}

TEST(isolation_tree, split_test_3) {
  matrix data(4, 3);
  // clang-format off
  data << 0.0,    11.0, 1.0, 
          8.0,    18.0, 1.0,
          9.0,    19.0, 1.0,
          10.0, 2000.0, 1.0;
  // clang-format on

  auto itree = isolation_tree::create();
  auto [above, below] = itree->split(data, 2, 1.0);

  matrix expected_below(4, 3);
  // clang-format off
  expected_below << 0.0,   11.0,  1.0, 
                    8.0,   18.0,  1.0,
                    9.0,   19.0,  1.0,
                   10.0, 2000.0, 1.0;
  // clang-format on

  EXPECT_TRUE(is_equal(below, expected_below));
}

TEST(isolation_tree, fit_error_1) {
  matrix data(0, 2);
  auto itree = isolation_tree::create();
  auto err = itree->fit(data, 10);
  EXPECT_TRUE(has_error(err)); // invalid matrix beacuse zero rows
}

TEST(isolation_tree, fit_error_2) {
  matrix data(2, 0);
  auto itree = isolation_tree::create();
  auto err = itree->fit(data, 10);
  EXPECT_TRUE(has_error(err)); // invalid matrix beacuse zero cols
}

TEST(isolation_tree, fit) {
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

  matrix data2(1, 2);
  // clang-format off
  data2 << -0.961607, -0.716857;
  //data2 << 40.4, 40.4;
  //  clang-format on

  auto itree = isolation_tree::create();
  itree->fit(data, 10);
  auto path_lengths = itree->path_lengths(data);
  // std::cout << path_lengths << std::endl;

  // TODO finish this test
}
