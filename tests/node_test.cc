#include "../src/node.h"
#include "../src/test.h"

#include "gtest/gtest.h"

TEST(node, create) {
  auto node = node::create(1, 1.0);

  EXPECT_TRUE(node->selected_feature == 1);
  EXPECT_TRUE(node->split_value == 1.0);
  EXPECT_TRUE(node->left_node == nullptr);
  EXPECT_TRUE(node->right_node == nullptr);
}

TEST(node, create_2) {
  auto left_node = node::create(2, 3.0);
  auto right_node = node::create(0, 3.2);
  auto node = node::create(1, 1.0);
  node->left_node = left_node;
  node->right_node = right_node;

  EXPECT_TRUE(node->selected_feature == 1);
  EXPECT_TRUE(node->split_value == 1.0);
  EXPECT_TRUE(node->left_node == left_node);
  EXPECT_TRUE(node->right_node == right_node);
}
