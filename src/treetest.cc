#include <gtest/gtest.h>
#include <initializer_list>
#include <set>
#include "set.h"

template <typename T>
void set_test_foo(s21::set<T> &a, std::set<T> &a_eth) {
  auto iter = *a.begin();
  auto iter_eth = a_eth.begin();
  for (;iter != *a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
    EXPECT_EQ(*iter, *iter_eth);
  }
  EXPECT_EQ(a.size(), a_eth.size());
}


TEST(set_default_constructor, 1) {
  // Arrange
  // Act
  s21::set<int> a;

  // Assert
  std::set<int> a_eth;
  set_test_foo(a, a_eth);
}

TEST(set_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::set<int> a{1, 2, 3};
  // Assert
  std::set<int> a_eth{1, 2, 3};
  set_test_foo(a, a_eth);
}

TEST(set_copy_constructor, 1) {
  // Arrange
  s21::set<int> b{1, 2, 3};
  // Act
  s21::set<int> a(b);
  // Assert
  std::set<int> b_eth{1, 2, 3};
  std::set<int> a_eth(b_eth);
  set_test_foo(a, a_eth);
}

TEST(set_move_constructor, 1) {
  // Arrange
  s21::set<int> b{1, 2, 3};
  // Act
  s21::set<int> a(std::move(b));
  // Assert
  std::set<int> b_eth{1, 2, 3};
  std::set<int> a_eth(std::move(b_eth));
  set_test_foo(a, a_eth);
  // set_test_foo(b, b_eth);
}

TEST(set_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::set<int> a;
  s21::set<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::set<int> b_eth{1, 2, 3};
  std::set<int> a_eth;
  a_eth = std::move(b_eth);
  set_test_foo(a, a_eth);
  // set_test_foo(b, b_eth);
}

TEST(set_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::set<int> a{3, 2, 1};
  s21::set<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::set<int> a_eth{3, 2, 1};
  std::set<int> b_eth{1, 2, 3};
  a_eth = std::move(b_eth);
  set_test_foo(a, a_eth);
  // set_test_foo(b, b_eth);
}

TEST(set_begin_iter, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto iter = *a.begin();
  // Assert
  std::set<int> a_eth{1, 2, 3};
  std::set<int>::iterator iter_eth = a_eth.begin();
  ASSERT_EQ(*iter, *iter_eth);
}


TEST(set_iterator_methods, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto iter = *a.begin();
  // Assert
  std::set<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  for (; iter != a.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(*iter, *iter_eth);
  }
}


TEST(set_empty, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  // Assert
  std::set<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_empty, 2) {
  // Arrange
  s21::set<int> a;
  // Act
  // Assert
  std::set<int> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_empty, 3) {
  // Arrange
  s21::set<std::string> a{"1", "2", "3", "4"};
  // Act
  // Assert
  std::set<std::string> a_eth{"1", "2", "3", "4"};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_size, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  // Assert
  std::set<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(set_max_size, 1) {
  // Arrange
  s21::set<int> a;
  // Act
  // Assert
  std::set<int> a_eth;
  ASSERT_EQ(a.max_size(),1000);
}

TEST(set_max_size, 2) {
  // Arrange
  s21::set<std::string> a;
  // Act
  // Assert
  std::set<std::string> a_eth;
  ASSERT_EQ(a.max_size(), 1000);
}

TEST(set_clear, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  a.clear();
  // Assert
  std::set<int> a_eth{1, 2, 3};
  a_eth.clear();
  set_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_clear, 2) {
  // Arrange
  s21::set<int> a{7, 5, 4, 6, 9, 8, 10, 11, -5};
  // Act
  a.clear();
  // Assert
  std::set<int> a_eth{7, 5, 4, 6, 9, 8, 10, 11, -5};
  a_eth.clear();
  set_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_clear, 3) {
  // Arrange
  s21::set<int> a{1, 2, 3, 4, 5};
  // Act
  a.clear();
  // Assert
  std::set<int> a_eth{1, 2, 3, 4, 5};
  a_eth.clear();
  set_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_clear, 4) {
  // Arrange
  s21::set<int> a{5, 4, 3, 2, 1};
  // Act
  a.clear();
  // Assert
  std::set<int> a_eth{5, 4, 3, 2, 1};
  a_eth.clear();
  set_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_clear, 5) {
  // Arrange
  s21::set<int> a;
  // Act
  // a.clear();
  // Assert
  std::set<int> a_eth;
  a_eth.clear();
  // set_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(set_insert, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  a.insert(7);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  a_eth.insert(7);
  set_test_foo(a, a_eth);
}

TEST(set_insert, 2) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  a.insert(3);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  a_eth.insert(3);
  set_test_foo(a, a_eth);
}

// TEST(set_insert, 3) {
//   // Arrange
//   s21::set<int> a;
//   // Act
//   a.insert(7);
//   // Assert
//   std::set<int> a_eth;
//   a_eth.insert(7);
//   set_test_foo(a, a_eth);
// }

TEST(set_insert, 4) {
  // Arrange
  s21::set<std::string> a{"1", "2", "3"};
  // Act
  a.insert("7");
  // Assert
  std::set<std::string> a_eth{"1", "2", "3"};
  a_eth.insert("7");
  set_test_foo(a, a_eth);
}

TEST(set_insert, 5) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  a.insert(3);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  a_eth.insert(3);
  set_test_foo(a, a_eth);
}

TEST(set_insert, 6) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  a.insert(-7);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  a_eth.insert(-7);
  set_test_foo(a, a_eth);
}

TEST(set_insert, 7) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto pair = a.insert(2);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  auto pair_eth = a_eth.insert(2);
  set_test_foo(a, a_eth);
  ASSERT_EQ(*pair.first, *pair_eth.first);
  ASSERT_EQ(pair.second, pair_eth.second);
}

TEST(set_erase, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  auto iter = a.root->get_down();
  // Act
  a.erase(iter);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  a_eth.erase(iter_eth);
  set_test_foo(a, a_eth);
}

TEST(set_erase, 2) {
  // Arrange
  s21::set<int> a{1, 2, 3};
auto iter = a.begin();
  // Act
  a.erase(iter);
  // Assert
  std::set<int> a_eth{ 2, 3};

  set_test_foo(a, a_eth);
}

TEST(set_erase, 3) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  auto iter = a.root->get_down();
  iter;
  // Act
  a.erase(iter);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  iter_eth;
  a_eth.erase(iter_eth);
  set_test_foo(a, a_eth);
}

// TEST(set_erase, 4) {
//   // Arrange
//   s21::set<int> a{1, 2, 3};
//   auto iter = a.root->get_last();
//   // Act
//   iter;
//   a.erase(iter);
//   // Assert
//   std::set<int> a_eth{1, 2};
//   set_test_foo(a, a_eth);
// }

TEST(set_erase, 6) {
  // Arrange
  s21::set<int> a{7, 9, 8};
  auto iter = a.root;
  // Act
  a.erase(iter);
  // Assert
  std::set<int> a_eth{ 9, 8};

  set_test_foo(a, a_eth);
}

TEST(set_erase, 7) {
  // Arrange
  s21::set<int> a{7, 6};
  auto iter = a.root;

  // Act
  a.erase(iter);
  // Assert
  std::set<int> a_eth{ 6};

  set_test_foo(a, a_eth);
}



TEST(set_swap, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  s21::set<int> b{4, 5};
  // Act
  a.swap(b);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  std::set<int> b_eth{4, 5};
  a_eth.swap(b_eth);
  set_test_foo(a, a_eth);
  set_test_foo(b, b_eth);
}

TEST(set_swap, 2) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  s21::set<int> b;
  // Act
  a.swap(b);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  std::set<int> b_eth;
  a_eth.swap(b_eth);
  set_test_foo(a, a_eth);
  set_test_foo(b, b_eth);
}

TEST(set_swap, 3) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  a.swap(a);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  a_eth.swap(a_eth);
  set_test_foo(a, a_eth);
}

TEST(set_merge, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  s21::set<int> b{4, 5};
  // Act
  a.merge(b);
  // Assert
  std::set<int> a_eth{1, 2, 3 ,4 ,5};


  set_test_foo(a, a_eth);

}

TEST(set_merge, 2) {
  // Arrange
  s21::set<int> a;
  s21::set<int> b{4, 5};
  // Act
  a.merge(b);
  // Assert

  std::set<int> a_eth{4, 5};

  set_test_foo(a, a_eth);

}

TEST(set_merge, 3) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  s21::set<int> b;
  // Act
  a.merge(b);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  std::set<int> b_eth;
  a_eth.merge(b_eth);
  set_test_foo(a, a_eth);
  set_test_foo(b, b_eth);
}

TEST(set_merge, 4) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  s21::set<int> b{8, 5, 2, };
  // Act
  a.merge(b);
  // Assert
  std::set<int> a_eth{1, 2, 3 , 8 ,5 ,2};

  
  set_test_foo(a, a_eth);

}

TEST(set_merge, 5) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  s21::set<int> b{1, 2, 3};
  // Act
  a.merge(b);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  
  set_test_foo(a, a_eth);

}

TEST(set_find, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto iter = a.find(1);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.find(1);
  ASSERT_EQ(**iter, *iter_eth);
}

TEST(set_find, 2) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto iter = a.find(3);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.find(3);
  ASSERT_EQ(**iter, *iter_eth);
}

TEST(set_find, 3) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto iter = a.find(7);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.find(7);
  ASSERT_EQ(**iter, *iter_eth);
}

TEST(set_contains, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  bool res = a.contains(2);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  bool res_eth = a.contains(2);
  ASSERT_EQ(res, res_eth);
}

TEST(set_contains, 2) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  bool res = a.contains(7);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  bool res_eth = a.contains(7);
  ASSERT_EQ(res, res_eth);
}

TEST(set_emplace, 1) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto res = a.insert_many(4, 5, 6);
  // Assert
  std::set<int> a_eth{1, 2, 3, 4, 5, 6};
  std::vector<std::pair<int, bool>> res_eth{std::pair<int, bool>(4, true),
                                            std::pair<int, bool>(5, true),
                                            std::pair<int, bool>(6, true)};
  auto iter_eth = res_eth.begin();
  for (auto iter : res) {
    ASSERT_EQ(*(iter.first), (*iter_eth).first);
    ASSERT_EQ(iter.second, (*iter_eth).second);
    ++iter_eth;
  }
  set_test_foo(a, a_eth);
}

TEST(set_emplace, 2) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto res = a.insert_many(1, 2, 3);
  // Assert
  std::set<int> a_eth{1, 2, 3};
  for (auto iter : res) {
    // ASSERT_EQ(iter.first, a.end());
    ASSERT_EQ(iter.second, false);
  }
  set_test_foo(a, a_eth);
}

TEST(set_emplace, 3) {
  // Arrange
  s21::set<int> a{1, 2, 3};
  // Act
  auto res = a.insert_many(4, 3, 6);
  // Assert
  std::set<int> a_eth{1, 2, 3, 4, 6};
  std::vector<std::pair<int, bool>> res_eth{std::pair<int, bool>(4, true),
                                            std::pair<int, bool>(3, false),
                                            std::pair<int, bool>(6, true)};
  auto iter_eth = res_eth.begin();
  for (auto iter : res) {
    // ASSERT_EQ(*(iter.first), (*iter_eth).first);
    ASSERT_EQ(iter.second, (*iter_eth).second);
    ++iter_eth;
  }
  set_test_foo(a, a_eth);
}


int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
