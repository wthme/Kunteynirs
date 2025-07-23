#include <gtest/gtest.h>
#include <map>
#include "map.h"
#include <iostream>
// #include "Btree.h"


// #include "../s21_containers.h"
// #include "../s21_containersplus.h"
// #include "../list.h"

template <typename T, typename V>
void map_test_foo(s21::map<T, V> &a, std::map<T, V> &a_eth) {
  auto iter = *a.begin();
  auto iter_eth = a_eth.begin();
  for (; iter != *a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(iter.key, iter_eth->first);
    ASSERT_EQ(iter.value, iter_eth->second);
  }
}



TEST(map_default_constructor, 1) {
  // Arrange
  // Act
  s21::map<int, std::string> a;
  // Assert
  std::map<int, std::string> a_eth;
  map_test_foo(a, a_eth);
}

TEST(map_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  map_test_foo(a, a_eth);
}

TEST(map_copy_constructor, 1) {
  // Arrange
  s21::map<int, std::string> b{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  s21::map<int, std::string> a(b);
  // Assert
  std::map<int, std::string> b_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  std::map<int, std::string> a_eth(b_eth);
  map_test_foo(a, a_eth);
}

TEST(map_move_constructor, 1) {
  // Arrange
  s21::map<int, std::string> b{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  s21::map<int, std::string> a(std::move(b));
  // Assert
  std::map<int, std::string> b_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  std::map<int, std::string> a_eth(std::move(b_eth));
  map_test_foo(a, a_eth);
  // map_test_foo(b, b_eth);
}

TEST(map_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::map<int, std::string> a;
  s21::map<int, std::string> b{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  a = std::move(b);
  // Assert
  std::map<int, std::string> b_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  std::map<int, std::string> a_eth;
  a_eth = std::move(b_eth);
  map_test_foo(a, a_eth);
  // map_test_foo(b, b_eth);
}

TEST(map_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  s21::map<int, std::string> b{std::pair<int, std::string>(4, "4"),
                               std::pair<int, std::string>(4, "4"),
                               std::pair<int, std::string>(4, "4")};
  // Act
  a = std::move(b);
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  std::map<int, std::string> b_eth{std::pair<int, std::string>(4, "4"),
                                   std::pair<int, std::string>(4, "4"),
                                   std::pair<int, std::string>(4, "4")};
  a_eth = std::move(b_eth);
  map_test_foo(a, a_eth);
  // map_test_foo(b, b_eth);
}

TEST(map_begin_iter, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto iter = *a.begin();
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  auto iter_eth = a_eth.begin();
  ASSERT_EQ(iter.key, iter_eth->first);
  ASSERT_EQ(iter.value, iter_eth->second);
}



TEST(map_iterator_methods, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto iter = *a.begin();
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  auto iter_eth = a_eth.begin();
  for (; iter != a.end(); ++iter, ++iter_eth) {
  ASSERT_EQ(iter.key, iter_eth->first);
  ASSERT_EQ(iter.value, iter_eth->second);
  }
}


TEST(map_at, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  ASSERT_EQ(a.at(1), a_eth.at(1));
  ASSERT_EQ(a.at(2), a_eth.at(2));
  ASSERT_EQ(a.at(3), a_eth.at(3));
}



TEST(map_square_brackets, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  ASSERT_EQ(a[1], a_eth[1]);
  ASSERT_EQ(a[2], a_eth[2]);
  ASSERT_EQ(a[3], a_eth[3]);
}


TEST(map_empty, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(map_empty, 2) {
  // Arrange
  s21::map<int, std::string> a;
  // Act
  // Assert
  std::map<int, std::string> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(map_size, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(map_max_size, 1) {
  // Arrange
  s21::map<int, std::string> a;
  // Act
  // Assert
  std::map<int, std::string> a_eth;
  ASSERT_EQ(a.max_size(), 1000);
}

TEST(map_max_size, 2) {
  // Arrange
  s21::map<int, int> a;
  // Act
  // Assert
  std::map<int, int> a_eth;
  ASSERT_EQ(a.max_size(), 1000);
}

TEST(map_clear, 1) {
  // Arrange
  s21::map<int, int> a{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                       std::pair<int, int>(2, 3)};
  // Act
  a.clear();
  // Assert
  std::map<int, int> a_eth{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                           std::pair<int, int>(2, 3)};
  a_eth.clear();
  map_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(map_clear, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(7, "7"),
                               std::pair<int, std::string>(5, "5"),
                               std::pair<int, std::string>(4, "4"),
                               std::pair<int, std::string>(6, "6"),
                               std::pair<int, std::string>(9, "9"),
                               std::pair<int, std::string>(8, "8"),
                               std::pair<int, std::string>(10, "10"),
                               std::pair<int, std::string>(11, "11"),
                               std::pair<int, std::string>(-5, "-5")};
  // Act
  a.clear();
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(7, "7"),
                                   std::pair<int, std::string>(5, "5"),
                                   std::pair<int, std::string>(4, "4"),
                                   std::pair<int, std::string>(6, "6"),
                                   std::pair<int, std::string>(9, "9"),
                                   std::pair<int, std::string>(8, "8"),
                                   std::pair<int, std::string>(10, "10"),
                                   std::pair<int, std::string>(11, "11"),
                                   std::pair<int, std::string>(-5, "-5")};
  a_eth.clear();
  map_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(map_clear, 3) {
  // Arrange
  s21::map<int, std::string> a{
      std::pair<int, std::string>(1, "1"), std::pair<int, std::string>(2, "2"),
      std::pair<int, std::string>(3, "3"), std::pair<int, std::string>(4, "4"),
      std::pair<int, std::string>(5, "5")};
  // Act
  a.clear();
  // Assert
  std::map<int, std::string> a_eth{
      std::pair<int, std::string>(1, "1"), std::pair<int, std::string>(2, "2"),
      std::pair<int, std::string>(3, "3"), std::pair<int, std::string>(4, "4"),
      std::pair<int, std::string>(5, "5")};
  a_eth.clear();
  map_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(map_clear, 4) {
  // Arrange
  s21::map<int, std::string> a{
      std::pair<int, std::string>(5, "5"), std::pair<int, std::string>(4, "4"),
      std::pair<int, std::string>(3, "3"), std::pair<int, std::string>(2, "2"),
      std::pair<int, std::string>(1, "1")};
  // Act
  a.clear();
  // Assert
  std::map<int, std::string> a_eth{
      std::pair<int, std::string>(5, "5"), std::pair<int, std::string>(4, "4"),
      std::pair<int, std::string>(3, "3"), std::pair<int, std::string>(2, "2"),
      std::pair<int, std::string>(1, "1")};
  a_eth.clear();
  map_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

// TEST(map_clear, 5) {
//   // Arrange
//   s21::map<float, double> a;
//   // Act
//   a.clear();
//   // Assert
//   std::map<float, double> a_eth;
//   a_eth.clear();
//   map_test_foo(a, a_eth);
//   ASSERT_EQ(a.empty(), a_eth.empty());
// }

TEST(map_insert_value_type, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto pair = a.insert(std::pair<int, std::string>(1, "1"));
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  auto pair_eth = a_eth.insert(std::pair<int, std::string>(1, "1"));
  map_test_foo(a, a_eth);
  // ASSERT_EQ(pair.first->first, pair_eth.first->first);
  // ASSERT_EQ(pair.first->second, pair_eth.first->second);
  ASSERT_EQ(pair.second, pair_eth.second);
}

TEST(map_insert_value_type, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto pair = a.insert(std::pair<int, std::string>(7, "1"));
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  auto pair_eth = a_eth.insert(std::pair<int, std::string>(7, "1"));
  map_test_foo(a, a_eth);
  // ASSERT_EQ(pair.first->first, pair_eth.first->first);
  // ASSERT_EQ(pair.first->second, pair_eth.first->second);
  ASSERT_EQ(pair.second, pair_eth.second);
}

TEST(map_insert_key_obj, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto pair = a.insert(1, "1");
  // Assert
  ASSERT_EQ(pair.second, false);
  ASSERT_EQ(a[1], "1");
}

TEST(map_insert_key_obj, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto pair = a.insert(7, "7");
  // Assert
  ASSERT_EQ(pair.second, true);
  // ASSERT_EQ(pair.first->first, 7);
  // ASSERT_EQ(pair.first->second, "7");
}

TEST(map_insert_or_assign, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto pair = a.insert_or_assign(1, "7");
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  auto pair_eth = a_eth.insert_or_assign(1, "7");
  map_test_foo(a, a_eth);
  // ASSERT_EQ(pair.first->first, pair_eth.first->first);
  // ASSERT_EQ(pair.first->second, pair_eth.first->second);
  ASSERT_EQ(pair.second, pair_eth.second);
}

TEST(map_insert_or_assign, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto pair = a.insert_or_assign(7, "7");
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  auto pair_eth = a_eth.insert_or_assign(7, "7");
  map_test_foo(a, a_eth);
  // ASSERT_EQ(pair.first->first, pair_eth.first->first);
  // ASSERT_EQ(pair.first->second, pair_eth.first->second);
  ASSERT_EQ(pair.second, pair_eth.second);
}

TEST(map_erase, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  auto iter = a.begin();
  // Act
  a.erase(iter);
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  auto iter_eth = a_eth.begin();
  a_eth.erase(iter_eth);
  map_test_foo(a, a_eth);
}


// TEST(map_erase, 3) {
//   // Arrange
//   s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
//                                std::pair<int, std::string>(2, "2"),
//                                std::pair<int, std::string>(3, "3")};
//   auto iter = a.begin();
//   ++iter;
//   // Act
//   a.erase(iter);
//   // Assert
//   std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
//                                    std::pair<int, std::string>(2, "2"),
//                                    std::pair<int, std::string>(3, "3")};
//   auto iter_eth = a_eth.begin();
//   ++iter_eth;
//   a_eth.erase(iter_eth);
//   map_test_foo(a, a_eth);
// }


TEST(map_swap, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  s21::map<int, std::string> b{std::pair<int, std::string>(4, "4"),
                               std::pair<int, std::string>(5, "5")};
  // Act
  a.swap(b);
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  std::map<int, std::string> b_eth{std::pair<int, std::string>(4, "4"),
                                   std::pair<int, std::string>(5, "5")};
  a_eth.swap(b_eth);
  map_test_foo(a, a_eth);
  map_test_foo(b, b_eth);
}

TEST(map_swap, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  s21::map<int, std::string> b;
  // Act
  a.swap(b);
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  std::map<int, std::string> b_eth;
  a_eth.swap(b_eth);
  map_test_foo(a, a_eth);
  map_test_foo(b, b_eth);
}

TEST(map_swap, 3) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  a.swap(a);
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  a_eth.swap(a_eth);
  map_test_foo(a, a_eth);
}


TEST(map_merge, 2) {
  // Arrange
  s21::map<int, std::string> a;
  s21::map<int, std::string> b{std::pair<int, std::string>(4, "4"),
                               std::pair<int, std::string>(5, "5")};
  // Act
  a.merge(b);
  // Assert
  std::map<int, std::string> a_eth;
  std::map<int, std::string> b_eth{std::pair<int, std::string>(4, "4"),
                                   std::pair<int, std::string>(5, "5")};
  a_eth.merge(b_eth);
  map_test_foo(a, a_eth);
  // map_test_foo(b, b_eth);
}




TEST(map_contains, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  bool res = a.contains(2);
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  bool res_eth = a.contains(2);
  ASSERT_EQ(res, res_eth);
}

TEST(map_contains, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  bool res = a.contains(7);
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  bool res_eth = a.contains(7);
  ASSERT_EQ(res, res_eth);
}

TEST(map_emplace, 1) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto res = a.insert_many(std::pair<int, std::string>(4, "4"),
                       std::pair<int, std::string>(5, "5"),
                       std::pair<int, std::string>(6, "6"));
  // Assert
  std::map<int, std::string> a_eth{
      std::pair<int, std::string>(1, "1"), std::pair<int, std::string>(2, "2"),
      std::pair<int, std::string>(3, "3"), std::pair<int, std::string>(4, "4"),
      std::pair<int, std::string>(5, "5"), std::pair<int, std::string>(6, "6")};
  std::vector<std::pair<std::string, bool>> res_eth{
      std::pair<std::string, bool>("4", true),
      std::pair<std::string, bool>("5", true),
      std::pair<std::string, bool>("6", true)};
  auto iter_eth = res_eth.begin();
  for (auto iter : res) {
    // ASSERT_EQ((*(iter.first)).second, (*iter_eth).first);
    ASSERT_EQ(iter.second, (*iter_eth).second);
    ++iter_eth;
  }
  map_test_foo(a, a_eth);
}

TEST(map_emplace, 2) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto res = a.insert_many(std::pair<int, std::string>(1, "4"),
                       std::pair<int, std::string>(2, "5"),
                       std::pair<int, std::string>(3, "6"));
  // Assert
  std::map<int, std::string> a_eth{std::pair<int, std::string>(1, "1"),
                                   std::pair<int, std::string>(2, "2"),
                                   std::pair<int, std::string>(3, "3")};
  std::vector<std::pair<std::string, bool>> res_eth{
      std::pair<std::string, bool>("4", false),
      std::pair<std::string, bool>("5", false),
      std::pair<std::string, bool>("6", false)};
  auto iter_eth = res_eth.begin();
  for (auto iter : res) {
    // ASSERT_EQ((*(iter.first)).second, (*iter_eth).first);
    ASSERT_EQ(iter.second, (*iter_eth).second);
    ++iter_eth;
  }
  map_test_foo(a, a_eth);
}

TEST(map_emplace, 3) {
  // Arrange
  s21::map<int, std::string> a{std::pair<int, std::string>(1, "1"),
                               std::pair<int, std::string>(2, "2"),
                               std::pair<int, std::string>(3, "3")};
  // Act
  auto res = a.insert_many(std::pair<int, std::string>(4, "4"),
                       std::pair<int, std::string>(3, "5"),
                       std::pair<int, std::string>(6, "6"));
  // Assert
  std::map<int, std::string> a_eth{
      std::pair<int, std::string>(1, "1"), std::pair<int, std::string>(2, "2"),
      std::pair<int, std::string>(3, "3"), std::pair<int, std::string>(4, "4"),
      std::pair<int, std::string>(6, "6")};
  std::vector<std::pair<std::string, bool>> res_eth{
      std::pair<std::string, bool>("4", true),
      std::pair<std::string, bool>("5", false),
      std::pair<std::string, bool>("6", true)};
  auto iter_eth = res_eth.begin();
  for (auto iter : res) {
    // ASSERT_EQ((*(iter.first)).second, (*iter_eth).first);
    ASSERT_EQ(iter.second, (*iter_eth).second);
    ++iter_eth;
  }
  map_test_foo(a, a_eth);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}