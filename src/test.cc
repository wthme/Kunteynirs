#include <gtest/gtest.h>

#include <array>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

using s21::Queue;
using std::queue;
using stek = s21::stack<int>;

void check_stacks(stek one, std::stack<int> second){
while(one.size() != 0){
    EXPECT_EQ(one.top(), second.top());
        one.pop();
        second.pop();
  }
}

template <typename T>
void list_test_foo(s21::list<T> &a, std::list<T> &a_eth) {
  auto iter = a.begin();
  auto iter_eth = a_eth.begin();
  for (; iter != a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(*iter, *iter_eth);
  }
  iter = a.end();
  iter_eth = a_eth.end();
  for (; iter != a.begin() && iter_eth != a_eth.begin();) {
    --iter;
    --iter_eth;
    ASSERT_EQ(*iter, *iter_eth);
  }
  ASSERT_EQ(a.size(), a_eth.size());
}

template <typename T>
void set_test_foo(s21::set<T> &a, std::set<T> &a_eth) {
  auto iter = *a.begin();
  auto iter_eth = a_eth.begin();
  for (;iter != *a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
    EXPECT_EQ(*iter, *iter_eth);
  }
  EXPECT_EQ(a.size(), a_eth.size());
}

template <typename T>
void multiset_test_foo(s21::multiset<T> &a, std::multiset<T> &a_eth) {
  auto iter = *a.begin();
  auto iter_eth = a_eth.begin();
  for (; iter != *a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(*iter, *iter_eth);
  }
  iter = a.end();
  iter_eth = a_eth.end();
  ASSERT_EQ(a.size(), a_eth.size());
}

template <typename T, typename V>
void map_test_foo(s21::map<T, V> &a, std::map<T, V> &a_eth) {
  auto iter = *a.begin();
  auto iter_eth = a_eth.begin();
  for (; iter != *a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(iter.key, iter_eth->first);
    ASSERT_EQ(iter.value, iter_eth->second);
  }
}

TEST(queue, 1) {
  Queue<int> q = Queue<int>();
  queue<int> stdq = queue<int>();

  for (int i = 0; i < 15; ++i) {
    stdq.push(4);
    q.push(4);
    const int &a = q.front();
    const int &b = stdq.front();

    EXPECT_EQ(a, b);
  }

  stdq.push(4);
  q.push(4);
  const int &a = q.front();
  const int &b = stdq.front();

  EXPECT_EQ(a, b);
}

TEST(queue, 2) {
  Queue<int> q;
  queue<int> stdq;
  stdq.push(3);
  q.push(3);
  auto a = q.front();
  auto b = stdq.front();

  EXPECT_EQ(a, b);
}

TEST(queue, 3) {
  Queue<int> q = Queue<int>();
  queue<int> stdq = queue<int>();
  stdq.push(3);
  q.push(3);
  for (int i = 0; i < 15; ++i) {
    stdq.push(i);
    q.push(i);

    const int &a = q.back();
    const int &b = stdq.back();
    EXPECT_EQ(a, b);
  }
  const int &a = q.front();
  const int &b = stdq.front();

  EXPECT_EQ(a, b);
}

TEST(queue, 4) {
  Queue<int> q = Queue<int>();
  queue<int> stdq = queue<int>();

  for (int i = 0; i < 15; ++i) {
    stdq.push(i);
    q.push(i);
  }

  for (int i = 0; i < 14; ++i) {
    stdq.pop();
    q.pop();
    const int &a = q.back();
    const int &b = stdq.back();

    EXPECT_EQ(a, b);
  }
  const int &a = q.front();
  const int &b = stdq.front();

  EXPECT_EQ(a, b);
}

TEST(queue, 5) {
  Queue<int> q = Queue<int>();
  queue<int> stdq = queue<int>();

  for (int i = 0; i < 15; ++i) {
    stdq.push(i);
    q.push(i);
  }

  for (int i = 0; i < 13; ++i) {
    stdq.pop();
    q.pop();
    const int &a = q.front();
    const int &b = stdq.front();
    EXPECT_EQ(a, b);
  }
  const int &a = q.front();
  const int &b = stdq.front();

  EXPECT_EQ(a, b);
}

TEST(queue_initlist, 1) {
  Queue<int> q{1, 4, 5};

  const int &a = q.front();
  const int &b = q.back();

  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 5);
}

TEST(copy, 1) {
  Queue<int> q = Queue<int>{4, 5, 6, 88, 6};

  Queue<int> b = q;

  EXPECT_FALSE(b.empty());
  EXPECT_FALSE(q.empty());
}

TEST(Queue, 1) {
  std::queue<int> stdq;
  Queue<int> q;

  stdq.push(4);
  q.push(4);

  EXPECT_EQ(q.front(), stdq.front());
}

TEST(Queue_default_constructor, 1) {
  // Arrange
  // Act
  s21::Queue<int> a;
  // Assert
  std::queue<int> a_eth;
  EXPECT_EQ(a.get_size(), a_eth.size());
}

TEST(Queue_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::Queue<int> a{1, 2, 3};
  // Assert
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.get_size(), a_eth.size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.front(), a_eth.front());
    a.pop();
    a_eth.pop();
  }
}

TEST(Queue_copy_constructor, 1) {
  // Arrange
  s21::Queue<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  s21::Queue<int> a(b);
  // Assert
  std::queue<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  std::queue<int> a_eth(b_eth);
  ASSERT_EQ(a.get_size(), a_eth.size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.front(), a_eth.front());
    a.pop();
    a_eth.pop();
  }
}

TEST(queue_move_constructor, 1) {
  // Arrange
  s21::Queue<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  s21::Queue<int> a(std::move(b));
  // Assert
  std::queue<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  std::queue<int> a_eth(std::move(b_eth));
  ASSERT_EQ(a.get_size(), a_eth.size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.front(), a_eth.front());
    a.pop();
    a_eth.pop();
  }
}

TEST(Queue_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::Queue<int> a;
  s21::Queue<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a = std::move(b);
  // Assert
  std::queue<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);

  std::queue<int> a_eth;
  a_eth = std::move(b_eth);

  ASSERT_EQ(a.get_size(), a.get_size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.front(), a.front());
    a.pop();
    a_eth.pop();
  }
}

TEST(Queue_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::Queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  s21::Queue<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a = std::move(b);
  // Assert
  std::queue<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  a_eth = std::move(b_eth);
  ASSERT_EQ(a.get_size(), a_eth.size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.front(), a_eth.front());
    a.pop();
    a_eth.pop();
  }
}

TEST(Queue_front, 1) {
  // Arrange
  s21::Queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  // Act
  // Assert
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.front(), a_eth.front());
}

TEST(Queue_back, 1) {
  // Arrange
  s21::Queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  // Act
  // Assert
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.back(), a_eth.back());
}

TEST(Queue_empty, 1) {
  // Arrange
  s21::Queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  // Act
  // Assert
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(Queue_empty, 2) {
  // Arrange
  s21::Queue<int> a;
  // Act
  // Assert
  std::queue<int> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(Queue_size, 1) {
  // Arrange
  s21::Queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  // Act
  // Assert
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.get_size(), a_eth.size());
}

TEST(Queue_size, 2) {
  // Arrange
  s21::Queue<int> a;
  // Act
  // Assert
  std::queue<int> a_eth;
  ASSERT_EQ(a.get_size(), a_eth.size());
}

TEST(Queue_push, 1) {
  // Arrange
  s21::Queue<int> a;
  // Act
  a.push(7);
  // Assert
  std::queue<int> a_eth;
  a_eth.push(7);
  ASSERT_EQ(a.front(), a_eth.front());
  ASSERT_EQ(a.back(), a_eth.back());
  ASSERT_EQ(a.get_size(), a_eth.size());
}

TEST(Queue_push, 2) {
  // Arrange
  s21::Queue<int> a;
  // Act
  a.push(1);
  a.push(2);
  a.push(3);
  // Assert
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.get_size(), a_eth.size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.back(), a_eth.back());
    ASSERT_EQ(a.front(), a_eth.front());
    a.pop();
    a_eth.pop();
  }
}

TEST(Queue_pop, 1) {
  // Arrange
  s21::Queue<int> a{1};
  // Act
  try {
    a.pop();
  } catch (...) {
  };
  // Assert
  std::queue<int> a_eth;
  // a_eth.push(8);
  // a_eth.pop();
  ASSERT_EQ(a.get_size(), a_eth.size());
}

TEST(Queue_pop, 2) {
  // Arrange
  s21::Queue<int> a;
  // Act
  a.push(1);
  a.push(2);
  a.push(3);
  // Assert
  std::queue<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  while (a.get_size() != 0) {
    a.pop();
    a_eth.pop();
    ASSERT_EQ(a.get_size(), a_eth.size());
  }
}

TEST(Queue_swap, 1) {
  // Arrange
  s21::Queue<int> a;
  s21::Queue<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a.swap(b);
  // Assert
  std::queue<int> a_eth;
  std::queue<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  a_eth.swap(b_eth);
  ASSERT_EQ(a.get_size(), a_eth.size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.front(), a_eth.front());
    ASSERT_EQ(a.back(), a_eth.back());
    a.pop();
    a_eth.pop();
  }
  ASSERT_EQ(b.get_size(), b_eth.size());
}

TEST(Queue_swap, 2) {
  // Arrange
  s21::Queue<int> a;
  a.push(4);
  a.push(5);
  s21::Queue<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a.swap(b);
  // Assert
  std::queue<int> a_eth;
  a_eth.push(4);
  a_eth.push(5);
  std::queue<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  a_eth.swap(b_eth);
  ASSERT_EQ(a.get_size(), a_eth.size());
  while (a.get_size() != 0) {
    ASSERT_EQ(a.front(), a_eth.front());
    ASSERT_EQ(a.back(), a_eth.back());
    a.pop();
    a_eth.pop();
  }
  ASSERT_EQ(b.get_size(), b_eth.size());
  while (b.get_size() != 0) {
    ASSERT_EQ(b.front(), b_eth.front());
    ASSERT_EQ(b.back(), b_eth.back());
    b.pop();
    b_eth.pop();
  }
}

TEST(vector_default_constructor, 1) {
  // Arrange
  // Act
  s21::vector<int> a;
  // Assert
  std::vector<int> a_eth;
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::vector<int> a(5);
  // Assert
  std::vector<int> a_eth(5);
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_parameterized_constructor, 2) {
  // Arrange
  s21::vector<int> a;
  // Act
  // Assert
  EXPECT_THROW(s21::vector<int> b(a.max_size() + 1);, std::runtime_error);
}

TEST(vector_parameterized_constructor, 3) {
  // Arrange
  // Act
  s21::vector<int> a{1, 2, 3};
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
  // ASSERT_EQ(a.capacity(), a_eth.capacity());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_copy_constructor, 1) {
  // Arrange
  s21::vector<int> b{1, 2, 3};
  // Act
  s21::vector<int> a(b);
  // Assert
  std::vector<int> b_eth{1, 2, 3};
  std::vector<int> a_eth(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  // ASSERT_EQ(a.capacity(), a_eth.capacity());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_move_constructor, 1) {
  // Arrange
  s21::vector<int> b{1, 2, 3};
  // Act
  s21::vector<int> a(std::move(b));
  // Assert
  std::vector<int> b_eth{1, 2, 3};
  std::vector<int> a_eth(std::move(b_eth));
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::vector<int> a;
  s21::vector<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::vector<int> b_eth{1, 2, 3};
  std::vector<int> a_eth;
  a_eth = std::move(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());

  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::vector<int> a{3, 2, 1};
  s21::vector<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert

  std::vector<int> a_eth{3, 2, 1};
  std::vector<int> b_eth{1, 2, 3};
  a_eth = std::move(b_eth);

  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());

  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_at, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a.at(i), a_eth.at(i));
  }
}

TEST(vector_at, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a.at(-1), std::out_of_range);
}

TEST(vector_at, 3) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a.at(10), std::out_of_range);
}

TEST(vector_square_brackets, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_square_brackets, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a[-1], std::out_of_range);
}

TEST(vector_square_brackets, 3) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a[10], std::out_of_range);
}

TEST(vector_front, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.front(), a_eth.front());
}

TEST(vector_back, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.back(), a_eth.back());
}

TEST(vector_back, 2) {
  // Arrange
  s21::vector<int> a{1};
  // Act
  // Assert
  std::vector<int> a_eth{1};
  ASSERT_EQ(a.back(), a_eth.back());
}

TEST(vector_data, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  int *add = a.data();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  int *add_eth = a_eth.data();
  ASSERT_EQ(*add, *add_eth);
}

TEST(vector_begin_iter, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  int *iter = a.begin();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.begin();
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(vector_end_iter, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  int *iter = a.end();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.end();
  ASSERT_EQ(*--iter, *--iter_eth);
}

TEST(vector_end_iter, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  int *iter = a.end();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.end();
  ASSERT_EQ(*--iter, *--iter_eth);
}

TEST(vector_iterator_methods, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  auto iter = a.begin();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  for (; iter != a.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(*iter, *iter_eth);
  }
}

TEST(vector_iterator_methods, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  auto iter = a.end();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.end();
  for (; iter != a.begin();) {
    --iter;
    --iter_eth;
    ASSERT_EQ(*iter, *iter_eth);
  }
}

TEST(vector_empty, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(vector_empty, 2) {
  // Arrange
  s21::vector<int> a;
  // Act
  // Assert
  std::vector<int> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(vector_empty, 3) {
  // Arrange
  s21::vector<int> a(0);
  // Act
  // Assert
  std::vector<int> a_eth(0);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(vector_size, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(vector_max_size, 1) {
  // Arrange
  s21::vector<int> a;
  // Act
  // Assert
  std::vector<int> a_eth;
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(vector_max_size, 2) {
  // Arrange
  s21::vector<std::string> a{"qwert"};
  // Act
  // Assert
  std::vector<std::string> a_eth{"qwert"};
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(vector_max_size, 3) {
  // Arrange
  s21::vector<double> a;
  // Act
  // Assert
  std::vector<double> a_eth;
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(vector_reserve, 1) {
  // Arrange
  s21::vector<std::string> a;
  // Act
  a.reserve(8);
  // Assert
  std::vector<std::string> a_eth;
  a_eth.reserve(8);
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_reserve, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.reserve(1);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  a_eth.reserve(1);
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_reserve_moove, 1) {
  // Arrange
  s21::vector<int> b{1, 2, 3, 4, 5};
  s21::vector<int> a;
  a = std::move(b);
  b = std::move(a);

  std::vector<int> a_eth{1, 2, 3, 4, 5};

  // a_eth.reserve(6);
  // b.reserve(6);

  EXPECT_EQ(b.capacity(), a_eth.capacity());
  EXPECT_EQ(b.size(), a_eth.size());
}

TEST(vector_capacity, 1) {
  // Arrange
  s21::vector<int> a;
  // Act
  // Assert
  std::vector<int> a_eth;
  EXPECT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_capacity, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_shrink_to_fit, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.shrink_to_fit();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  a_eth.shrink_to_fit();
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_shrink_to_fit, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.reserve(9);
  a.shrink_to_fit();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  a_eth.reserve(9);
  a_eth.shrink_to_fit();

  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_clear, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.clear();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  a_eth.clear();
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
  ASSERT_EQ(*a.data(), *a_eth.data());
}

TEST(vector_insert, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  int *iter = a.begin();
  // Act
  a.insert(iter, 7);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.begin();
  a_eth.insert(iter_eth, 7);

  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert, 2) {
  s21::vector<int> a{1, 2, 3};
  int *iter = a.end();
  a.insert(iter, 7);

  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.end();
  a_eth.insert(iter_eth, 7);

  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert, 3) {
  // Arrange
  s21::vector<int> a;
  int *iter = a.begin();
  // Act
  a.insert(iter, 7);
  // Assert
  std::vector<int> a_eth;
  auto iter_eth = a_eth.begin();
  a_eth.insert(iter_eth, 7);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert, 4) {
  // Arrange
  s21::vector<int> a;
  int *iter = a.end();
  // Act
  a.insert(iter, 7);
  // Assert
  std::vector<int> a_eth;
  std::vector<int>::iterator iter_eth = a_eth.end();
  a_eth.insert(iter_eth, 7);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert, 5) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  int *iter = a.begin();
  // Act
  ++iter;
  a.insert(iter, 7);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.begin();
  ++iter_eth;
  a_eth.insert(iter_eth, 7);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_erase, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  auto iter = a.begin();
  // Act
  a.erase(iter);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.begin();
  a_eth.erase(iter_eth);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_erase, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  int *iter = a.end();
  // Act
  --iter;
  a.erase(iter);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int>::iterator iter_eth = a_eth.end();
  --iter_eth;
  a_eth.erase(iter_eth);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_push_back, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.push_back(7);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  a_eth.push_back(7);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_push_back, 2) {
  // Arrange
  s21::vector<int> a;
  // Act
  a.push_back(7);
  // Assert
  std::vector<int> a_eth;
  a_eth.push_back(7);
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_pop_back, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.pop_back();
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  a_eth.pop_back();
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_pop_back, 2) {
  // Arrange
  s21::vector<int> a;
  // Act
  EXPECT_THROW(a.pop_back(), std::out_of_range);
  // Assert
  std::vector<int> a_eth;

  // a_eth.pop_back();

  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_swap, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  s21::vector<int> b{4, 5};
  // Act
  a.swap(b);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int> b_eth{4, 5};
  a_eth.swap(b_eth);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
  for (int i = 0; i < b.size(); i++) {
    ASSERT_EQ(b[i], b_eth[i]);
  }
  ASSERT_EQ(b.size(), b_eth.size());
  ASSERT_EQ(b.capacity(), b_eth.capacity());
}

TEST(vector_swap, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  s21::vector<int> b;
  // Act
  a.swap(b);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  std::vector<int> b_eth;
  a_eth.swap(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
  for (int i = 0; i < b.size(); i++) {
    ASSERT_EQ(b[i], b_eth[i]);
  }
  ASSERT_EQ(b.size(), b_eth.size());
  ASSERT_EQ(b.capacity(), b_eth.capacity());
}

TEST(vector_swap, 3) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.swap(a);
  // Assert
  std::vector<int> a_eth{1, 2, 3};
  a_eth.swap(a_eth);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_multi_push, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  int *iter = a.begin();

  a.insert_many_back(4, 5, 6, 7);
  std::vector<int> a_eth{1, 2, 3, 4, 5, 6, 7};
  std::vector<int>::iterator iter_eth = a_eth.end();

  for (int i = 0; i < a.size(); i++) {
    EXPECT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_multi_push, 2) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  int *iter = a.end();
  a.insert_many_back(4, 5, 6, 7);
  std::vector<int> a_eth{1, 2, 3, 4, 5, 6, 7};
  std::vector<int>::iterator iter_eth = a_eth.end();

  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
  ASSERT_EQ(a.size(), a_eth.size());
  // ASSERT_EQ(a.capacity(), a_eth.capacity());
}

TEST(vector_multi_push, 3) {
  // Arrange
  s21::vector<int> a{1, 2, 3};

  a.insert_many_back(5, 6);
  std::vector<int> a_eth{1, 2, 3, 5, 6};
  std::vector<int>::iterator iter_eth = a_eth.end();

  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
  ASSERT_EQ(a.size(), a_eth.size());
  // ASSERT_EQ(a.capacity(), a_eth.capacity());
}

// TEST(vector_emplace, 2) {
//   // Arrange
//   s21::vector<int> a{1, 2, 3};
//   // Act
//   auto it = a.end();
//   a.insert_many_back(it, 4, 5, 6);
//   // Assert
//   std::vector<int> a_eth{1, 2, 3, 4, 5, 6};
//   ASSERT_EQ(a.size(), a_eth.size());
//   ASSERT_EQ(*it, 6);
//   for (int i = 0; i < a.size(); i++) {
//     ASSERT_EQ(a[i], a_eth[i]);
//   }
// }

TEST(vector_emplace_back, 1) {
  // Arrange
  s21::vector<int> a{1, 2, 3};
  // Act
  a.insert_many_back(4, 5, 6);
  // Assert
  std::vector<int> a_eth{1, 2, 3, 4, 5, 6};
  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_emplace, 1) {
  // Arrange
  s21::vector<int> a{4, 5, 6};
  // Act
  int *it = a.begin();
  a.insert_many(it, 1, 2, 3);
  // Assert
  std::vector<int> a_eth{1, 2, 3, 4, 5, 6};
  ASSERT_EQ(a.size(), a_eth.size());
  // ASSERT_EQ(*it, 3);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert_many_many, 1) {
  s21::vector<int> a{1, 2, 3, 4};
  int *iter = a.begin() + 2;
  // a.insert_many_back( 7 , 4 ,5);

  a.insert_many(iter, 77, 10);

  std::vector<int> a_eth{1, 2, 77, 10, 3, 4};
  std::vector<int>::iterator iter_eth = a_eth.end();

  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert_many_many, 2) {
  s21::vector<int> a{1, 2, 3, 4};
  int *iter = a.end();
  // a.insert_many_back( 7 , 4 ,5);

  a.insert_many(iter, 77, 10);

  std::vector<int> a_eth{1, 2, 3, 4, 77, 10};
  std::vector<int>::iterator iter_eth = a_eth.end();

  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert_many_many, 3) {
  s21::vector<int> a{1, 2, 3, 4};
  int *iter = a.begin();
  // a.insert_many_back( 7 , 4 ,5);

  a.insert_many(iter, 77, 10);

  std::vector<int> a_eth{77, 10, 1, 2, 3, 4};
  std::vector<int>::iterator iter_eth = a_eth.end();

  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(vector_insert_many_many, 4) {
  s21::vector<int> a{1, 2, 3, 4};
  int *iter = a.begin() - 1;
  // a.insert_many_back( 7 , 4 ,5);

  EXPECT_THROW(a.insert_many(iter, 77, 10), std::out_of_range);
}

TEST(vector_insert_many_many, 5) {
  s21::vector<int> a{1, 2, 3, 4};
  int *iter = a.end() + 3;
  // a.insert_many_back( 7 , 4 ,5);

  EXPECT_THROW(a.insert_many(iter, 77, 10), std::out_of_range);
}



TEST(stack_constructor_usial, 1){
    std::stack<int>  a;
    std::stack<int> a_eth;
    EXPECT_EQ(a.size(), a_eth.size());
}


TEST(stack_constructor_usial, 2){
    stek a(3);
    EXPECT_EQ(a.size(), 0);
}

TEST(param_cpnst, 1){ 
stek a;
EXPECT_EQ(a.size(), 0);
std::stack<int> b;
EXPECT_EQ(b.size(), 0);
EXPECT_EQ(a.size(), b.size());
b.push(1);
b.push(2);
b.push(3);
a.push(1);
a.push(2);
a.push(3);
check_stacks(a,b);
}

TEST(param_cpnst, 2){
std::stack<int> b;
b.push(1);
b.push(2);
b.push(3);
stek a{1,2,3};
stek t = stek(a);
stek n = stek(a);
check_stacks(a,b);
}



TEST(stack_default_constructor, 1) {
  // Arrange
  // Act
  s21::stack<int> a;
  // Assert
  std::stack<int> a_eth;
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(stack_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::stack<int> a{1, 2, 3};
  // Assert
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
}

TEST(stack_copy_constructor, 1) {
  // Arrange
  s21::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  s21::stack<int> a(b);
  // Assert
  std::stack<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  std::stack<int> a_eth(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
}

TEST(stack_move_constructor, 1) {
  // Arrange
  s21::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  s21::stack<int> a(std::move(b));
  // Assert
  std::stack<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  std::stack<int> a_eth(std::move(b_eth));
  ASSERT_EQ(a.size(), a_eth.size());

  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
}

TEST(stack_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::stack<int> a;
  s21::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a = std::move(b);
  // Assert
  std::stack<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  std::stack<int> a_eth;
  a_eth = std::move(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
}

TEST(stack_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::stack<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  s21::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a = std::move(b);
  // Assert
  std::stack<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  a_eth = std::move(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
}

TEST(stack_top, 1) {
  // Arrange
  s21::stack<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  // Act
  // Assert
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.top(), a_eth.top());
}

TEST(stack_empty, 1) {
  // Arrange
  s21::stack<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  // Act
  // Assert
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(stack_empty, 2) {
  // Arrange
  s21::stack<int> a;
  // Act
  // Assert
  std::stack<int> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(stack_size, 1) {
  // Arrange
  s21::stack<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  // Act
  // Assert
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(stack_size, 2) {
  // Arrange
  s21::stack<int> a;
  // Act
  // Assert
  std::stack<int> a_eth;
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(stack_push, 1) {
  // Arrange
  s21::stack<int> a;
  // Act
  a.push(7);
  // Assert
  std::stack<int> a_eth;
  a_eth.push(7);
  ASSERT_EQ(a.top(), a_eth.top());
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(stack_push, 2) {
  // Arrange
  s21::stack<int> a;
  // Act
  a.push(1);
  a.push(2);
  a.push(3);
  // Assert
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
}

TEST(stack_pop, 1) {
  // Arrange
    s21::stack<int> a;
  // Act
  EXPECT_THROW( a.pop(),std::out_of_range );
}

TEST(stack_pop, 2) {
  // Arrange
  s21::stack<int> a;
  // Act
  a.push(1);
  a.push(2);
  a.push(3);
  // Assert
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  while (a.size() != 0) {
    a.pop();
    a_eth.pop();
    ASSERT_EQ(a.size(), a_eth.size());
  }
}

TEST(stack_swap, 1) {
  // Arrange
  s21::stack<int> a;
  s21::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a.swap(b);
  // Assert
  std::stack<int> a_eth;
  std::stack<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  a_eth.swap(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
  ASSERT_EQ(b.size(), b_eth.size());
}

TEST(stack_swap, 2) {
  // Arrange
  s21::stack<int> a;
  a.push(4);
  a.push(5);
  s21::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  // Act
  a.swap(b);
  // Assert
  std::stack<int> a_eth;
  a_eth.push(4);
  a_eth.push(5);
  std::stack<int> b_eth;
  b_eth.push(1);
  b_eth.push(2);
  b_eth.push(3);
  a_eth.swap(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
  ASSERT_EQ(b.size(), b_eth.size());
  while (b.size() != 0) {
    ASSERT_EQ(b.top(), b_eth.top());
    b.pop();
    b_eth.pop();
  }
}

TEST(stack_emplace_front, 1) {
  // Arrange
  s21::stack<int> a{1, 2, 3};
  // Act
  a.insert_many_back(4, 5, 6);
  // Assert
  std::stack<int> a_eth;
  a_eth.push(1);
  a_eth.push(2);
  a_eth.push(3);
  a_eth.push(4);
  a_eth.push(5);
  a_eth.push(6);
  ASSERT_EQ(a.size(), a_eth.size());
  while (a.size() != 0) {
    ASSERT_EQ(a.top(), a_eth.top());
    a.pop();
    a_eth.pop();
  }
}


TEST(array_default_constructor, 1) {
  // Arrange
  // Act
  s21::array<int, 0> a;
  // Assert
  std::array<int, 0> a_eth;
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(array_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::array<int, 3> a{1, 2, 3};
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
  for (size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(array_parameterized_constructor, 2) {
  // Arrange
  // Act
  s21::array<int, 3> a{1, 2, 3};
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
  for (size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(array_copy_constructor, 1) {
  // Arrange
  s21::array<int, 3> b{1, 2, 3};
  // Act
  s21::array<int, 3> a(b);
  // Assert
  std::array<int, 3> b_eth{1, 2, 3};
  std::array<int, 3> a_eth(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(array_move_constructor, 1) {
  // Arrange
  s21::array<int, 3> b{1, 2, 3};
  // Act
  s21::array<int, 3> a(std::move(b));
  // Assert
  std::array<int, 3> b_eth{1, 2, 3};
  std::array<int, 3> a_eth(std::move(b_eth));
  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(array_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::array<int, 3> a;
  s21::array<int, 3> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::array<int, 3> a_eth;
  std::array<int, 3> b_eth{1, 2, 3};
  a_eth = std::move(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(array_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::array<int, 3> a{3, 2, 1};
  s21::array<int, 3> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::array<int, 3> a_eth{3, 2, 1};
  std::array<int, 3> b_eth{1, 2, 3};
  a_eth = std::move(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(array_at, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a.at(i), a_eth.at(i));
  }
}

TEST(array_at, 2) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a.at(-1), std::out_of_range);
}

TEST(array_at, 3) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a.at(10), std::out_of_range);
}

TEST(array_SquareBrackets, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
}

TEST(array_square_brackets, 2) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a[-1], std::out_of_range);
}

TEST(array_square_brackets, 3) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  ASSERT_THROW(a[10], std::out_of_range);
}

TEST(array_front, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  ASSERT_EQ(a.front(), a_eth.front());
}

TEST(array_back, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  ASSERT_EQ(a.back(), a_eth.back());
}

TEST(array_back, 2) {
  // Arrange
  s21::array<int, 1> a{1};
  // Act
  // Assert
  std::array<int, 1> a_eth{1};
  ASSERT_EQ(a.back(), a_eth.back());
}

TEST(array_data, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  int *add = a.data();
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  int *add_eth = a_eth.data();
  ASSERT_EQ(*add, *add_eth);
}

TEST(array_begin, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  int* iter = a.begin();
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  std::array<int, 3>::iterator iter_eth = a_eth.begin();
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(array_end, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  int* iter = a.end();
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  std::array<int, 3>::iterator iter_eth = a_eth.end();
  ASSERT_EQ(*--iter, *--iter_eth);
}

TEST(array_empty, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(array_empty, 2) {
  // Arrange
  s21::array<int, 5> a;
  // Act
  // Assert
  std::array<int, 5> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(array_empty, 3) {
  // Arrange
  s21::array<int, 0> a;
  // Act
  // Assert
  std::array<int, 0> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(array_size, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(array_max_size, 1) {
  // Arrange
  s21::array<int, 1> a;
  // Act
  // Assert
  std::array<int, 1> a_eth;
  ASSERT_EQ(a.max_size(), a_eth.max_size());
}

TEST(array_max_size, 2) {
  // Arrange
  s21::array<std::string, 1> a;
  // Act
  // Assert
  std::array<std::string, 1> a_eth;
  ASSERT_EQ(a.max_size(), a_eth.max_size());
}

TEST(array_swap, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  s21::array<int, 3> b{4, 5};
  // Act
  a.swap(b);
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  std::array<int, 3> b_eth{4, 5};
  a_eth.swap(b_eth);

  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }


  ASSERT_EQ(a_eth.size(), 3);

  for (int i = 0; i < b.size(); i++) {
    ASSERT_EQ(b[i], b_eth[i]);
  }
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(b.size(), 3);
}

TEST(array_swap, 2) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  s21::array<int, 3> b;
  // Act
  a.swap(b);
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  std::array<int, 3> b_eth;
  a_eth.swap(b_eth);
  ASSERT_EQ(a.size(), a_eth.size());
  for (int i = 0; i < b.size(); i++) {
    ASSERT_EQ(b[i], b_eth[i]);
  }
  ASSERT_EQ(b.size(), b_eth.size());
}

TEST(array_swap, 3) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  a.swap(a);
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  a_eth.swap(a_eth);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(array_fill, 1) {
  // Arrange
  s21::array<int, 7> a;
  // Act
  a.fill(7);
  // Assert
  std::array<int, 7> a_eth;
  a_eth.fill(7);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(array_fill, 2) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  a.fill(7);
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  a_eth.fill(7);
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], a_eth[i]);
  }
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(array_begin_iter, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  auto iter = a.begin();
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(array_end_iter, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  auto iter = a.end();
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  auto iter_eth = a_eth.end();
  --iter;
  --iter_eth;
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(array_iterator_methods, 1) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  auto iter = a.begin();
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  for (; iter != a.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(*iter, *iter_eth);
  }
}

TEST(array_iterator_methods, 2) {
  // Arrange
  s21::array<int, 3> a{1, 2, 3};
  // Act
  auto iter = a.end();
  // Assert
  std::array<int, 3> a_eth{1, 2, 3};
  auto iter_eth = a_eth.end();
  for (; iter != a.begin();) {
    --iter;
    --iter_eth;
    ASSERT_EQ(*iter, *iter_eth);
  }
}


TEST(list_default_constructor, 1) {
  // Arrange
  // Act
  s21::list<int> a;
  // Assert
  std::list<int> a_eth;
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(list_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::list<int> a(5);
  // Assert
  std::vector<int> a_eth(5);
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(list_parameterized_constructor, 2) {
  // Arrange
  s21::list<int> a;
  // Act
  // Assert
  ASSERT_THROW(s21::list<int> b(a.max_size() + 1);, std::runtime_error);
}

TEST(list_parameterized_constructor, 3) {
  // Arrange
  // Act
  s21::list<int> a{1, 2, 3};
  // Assert
  std::list<int> a_eth{1, 2, 3};
  list_test_foo(a, a_eth);
}

TEST(list_copy_constructor, 1) {
  // Arrange
  s21::list<int> b{1, 2, 3};
  // Act
  s21::list<int> a(b);
  // Assert
  std::list<int> b_eth{1, 2, 3};
  std::list<int> a_eth(b_eth);
  list_test_foo(a, a_eth);
}

TEST(list_move_constructor, 1) {
  // Arrange
  s21::list<int> b{1, 2, 3};
  // Act
  s21::list<int> a(std::move(b));
  // Assert
  std::list<int> b_eth{1, 2, 3};
  std::list<int> a_eth(std::move(b_eth));
  list_test_foo(a, a_eth);
}

TEST(list_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::list<int> a;
  s21::list<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::list<int> b_eth{1, 2, 3};
  std::list<int> a_eth;
  a_eth = std::move(b_eth);
  list_test_foo(a, a_eth);
}

TEST(list_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::list<int> a{3, 2, 1};
  s21::list<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::list<int> a_eth{3, 2, 1};
  std::list<int> b_eth{1, 2, 3};
  a_eth = std::move(b_eth);
  list_test_foo(a, a_eth);
}

TEST(list_front, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  // Assert
  std::list<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.front(), a_eth.front());
}

TEST(list_back, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  // Assert
  std::list<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.back(), a_eth.back());
}

TEST(list_back, 2) {
  // Arrange
  s21::list<int> a{1};
  // Act
  // Assert
  std::list<int> a_eth{1};
  ASSERT_EQ(a.back(), a_eth.back());
}

TEST(list_begin_iter, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  auto iter = a.begin();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  std::list<int>::iterator iter_eth = a_eth.begin();
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(list_end_iter, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  auto iter = a.end();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  std::list<int>::iterator iter_eth = a_eth.end();
  ASSERT_EQ(*--iter, *--iter_eth);
}

TEST(list_end_iter, 2) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  auto iter = a.end();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  std::list<int>::iterator iter_eth = a_eth.end();
  ASSERT_EQ(*--iter, *--iter_eth);
}

TEST(list_iterator_methods, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  auto iter = a.begin();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  for (; iter != a.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(*iter, *iter_eth);
  }
}

TEST(list_iterator_methods, 2) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  auto iter = a.end();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.end();
  for (; iter != a.begin();) {
    --iter;
    --iter_eth;
    ASSERT_EQ(*iter, *iter_eth);
  }
}

TEST(list_empty, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  // Assert
  std::list<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(list_empty, 2) {
  // Arrange
  s21::list<int> a;
  // Act
  // Assert
  std::list<int> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(list_empty, 3) {
  // Arrange
  s21::list<int> a(0);
  // Act
  // Assert
  std::list<int> a_eth(0);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(list_size, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  // Assert
  std::list<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(list_max_size, 1) {
  // Arrange
  s21::list<int> a;
  // Act
  // Assert
  std::list<int> a_eth;
  ASSERT_EQ(a.max_size(), a.max_size());
}

TEST(list_max_size, 2) {
  // Arrange
  s21::list<std::string> a;
  // Act
  // Assert
  std::list<std::string> a_eth;
  ASSERT_EQ(a.max_size(), a.max_size());
}

TEST(list_clear, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.clear();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.clear();
  ASSERT_EQ(a.size(), a_eth.size());
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(list_insert, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  auto iter = a.begin();
  // Act
  a.insert(iter.next->prev, 7);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  a_eth.insert(iter_eth, 7);
  list_test_foo(a, a_eth);
}

TEST(list_insert, 2) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  auto iter = a.end();
  // Act
  a.insert(&iter, 7);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.end();
  a_eth.insert(iter_eth, 7);
  list_test_foo(a, a_eth);
}

TEST(list_insert, 3) {
  // Arrange
  s21::list<int> a;
  auto iter = a.begin();
  // Act
  a.insert(&iter, 7);
  // Assert
  std::list<int> a_eth;
  auto iter_eth = a_eth.begin();
  a_eth.insert(iter_eth, 7);
  // list_test_foo(a, a_eth);
}

TEST(list_insert, 4) {
  // Arrange
  s21::list<int> a;
  auto iter = a.end();
  // Act
  a.insert(&iter, 7);
  // Assert
  std::list<int> a_eth;
  auto iter_eth = a_eth.end();
  a_eth.insert(iter_eth, 7);
  list_test_foo(a, a_eth);
}

TEST(list_insert, 5) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  auto iter = a.begin();
  // Act
  ++iter;
  a.insert(iter.next->prev, 7);
  // Assert
  std::list<int> c{1 ,7, 2, 3};

  list_test_foo(a, c);
}

TEST(list_erase, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  auto iter = a.begin();
  // Act
  a.erase(iter.next->prev);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  a_eth.erase(iter_eth);
  list_test_foo(a, a_eth);
}

TEST(list_erase, 2) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  auto iter = a.end();
  // Act
  --iter;
  a.erase(iter.prev->next);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.end();
  --iter_eth;
  a_eth.erase(iter_eth);
  list_test_foo(a, a_eth);
}

TEST(list_erase, 3) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  auto iter = a.begin();
  ++iter;
  // Act
  a.erase(iter.next->prev);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  ++iter_eth;
  a_eth.erase(iter_eth);
  list_test_foo(a, a_eth);
}

TEST(list_push_back, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.push_back(7);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.push_back(7);
  list_test_foo(a, a_eth);
}

TEST(list_push_back, 2) {
  // Arrange
  s21::list<int> a;
  // Act
  a.push_back(7);
  // Assert
  std::list<int> a_eth;
  a_eth.push_back(7);
  list_test_foo(a, a_eth);
}

TEST(list_pop_back, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.pop_back();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.pop_back();
  list_test_foo(a, a_eth);
}

TEST(list_pop_back, 2) {
  // Arrange
  s21::list<int> a{1};
  // Act
  a.pop_back();
  // Assert
  std::list<int> a_eth{1};
  a_eth.pop_back();
  list_test_foo(a, a_eth);
}

TEST(list_push_front, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.push_front(7);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.push_front(7);
  list_test_foo(a, a_eth);
}

TEST(list_push_front, 2) {
  // Arrange
  s21::list<int> a;
  // Act
  a.push_front(7);
  // Assert
  std::list<int> a_eth;
  a_eth.push_front(7);
  list_test_foo(a, a_eth);
}

TEST(list_pop_front, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.pop_front();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.pop_front();
  list_test_foo(a, a_eth);
}

TEST(list_pop_front, 2) {
  // Arrange
  s21::list<int> a{1};
  // Act
  a.pop_front();
  // Assert
  std::list<int> a_eth{1};
  a_eth.pop_front();
  list_test_foo(a, a_eth);
}

TEST(list_swap, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b{4, 5};
  // Act
  a.swap(b);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  std::list<int> b_eth{4, 5};
  a_eth.swap(b_eth);
  list_test_foo(a, a_eth);
  list_test_foo(b, b_eth);
}

TEST(list_swap, 2) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b;
  // Act
  a.swap(b);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  std::list<int> b_eth;
  a_eth.swap(b_eth);
  list_test_foo(a, a_eth);
  list_test_foo(b, b_eth);
}

TEST(list_swap, 3) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.swap(a);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.swap(a_eth);
  list_test_foo(a, a_eth);
}

TEST(list_merge, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b{4, 5};
  // Act
  a.merge(b);
  // Assert
  std::list<int> c{1, 2, 3 ,4 ,5};
  
  list_test_foo(a, c);

}

TEST(list_merge, 2) {
  // Arrange
  s21::list<int> a;
  s21::list<int> b{4, 5};
  // Act
  a.merge(b);
  // Assert
  s21::list<int> c{4, 5};

  // list_test_foo(b, c);

}

TEST(list_merge, 3) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b;
  // Act
  a.merge(b);
  // Assert
  std::list<int> c{1, 2, 3};

  list_test_foo(a, c);

}

TEST(list_merge, 4) {
  // Arrange
  s21::list<int> a{7, 8, 9};
  s21::list<int> b{1, 2, 3};
  // Act
  a.merge(b);
  // Assert
  std::list<int> c{7, 8, 9,1, 2, 3};

  list_test_foo(a, c);

}

TEST(list_splice, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b{4, 5};
  // Act
  auto  iter = a.begin();
  a.splice(iter.next->prev, b);
  // Assert
  std::list<int> c{4, 5, 1 , 2 ,3};

  list_test_foo(a, c);

}

TEST(list_splice, 2) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b{4, 5};
  // Act
  auto iter = a.begin();
  ++iter;
  a.splice(iter.prev->next, b);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  std::list<int> b_eth{4, 5};
  auto iter_eth = a_eth.begin();
  ++iter_eth;
  a_eth.splice(iter_eth, b_eth);
  list_test_foo(a, a_eth);
  list_test_foo(b, b_eth);
}

TEST(list_splice, 3) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b{4, 5};
  // Act
  auto iter = a.end();
  --iter;
  a.splice(iter.next->prev, b);
  // Assert
  std::list<int> a_eth{1, 2, 3};
  std::list<int> b_eth{4, 5};
  auto iter_eth = a_eth.end();
  --iter_eth;
  a_eth.splice(iter_eth, b_eth);
  list_test_foo(a, a_eth);
  list_test_foo(b, b_eth);
}

TEST(list_splice, 4) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b{4, 5};
  // Act
  auto iter = a.end();
  a.splice(a.end().prev->next, b);
  // Assert

  std::list<int> c{1,2,3,4,5};


  list_test_foo(a, c);

}


TEST(list_splice, 6) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  s21::list<int> b {0};
  // Act
  auto iter = a.begin();
  a.splice(iter.next->prev, b);
  // Assert
  std::list<int> a_eth{0,1, 2, 3};
 
  list_test_foo(a, a_eth);

}

TEST(list_reverse, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.reverse();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.reverse();
  list_test_foo(a, a_eth);
}

TEST(list_reverse, 2) {
  // Arrange
  s21::list<int> a;
  // Act
  a.reverse();
  // Assert
  std::list<int> a_eth;
  a_eth.reverse();
  list_test_foo(a, a_eth);
}

TEST(list_reverse, 3) {
  // Arrange
  s21::list<int> a{1};
  // Act
  a.reverse();
  // Assert
  std::list<int> a_eth{1};
  a_eth.reverse();
  list_test_foo(a, a_eth);
}

TEST(list_unique, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.unique();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.unique();
  list_test_foo(a, a_eth);
}

TEST(list_unique, 2) {
  // Arrange
  s21::list<int> a{1, 1, 1, 2, 3};
  // Act
  a.unique();
  // Assert
  std::list<int> a_eth{1, 1, 1, 2, 3};
  a_eth.unique();
  list_test_foo(a, a_eth);
}

TEST(list_unique, 3) {
  // Arrange
  s21::list<int> a{1};
  // Act
  a.unique();
  // Assert
  std::list<int> a_eth{1};
  a_eth.unique();
  list_test_foo(a, a_eth);
}

TEST(list_unique, 4) {
  // Arrange
  s21::list<int> a{1, 1, 1, 2, 3, 1, 1, 7, 7};
  // Act
  a.unique();
  // Assert
  std::list<int> a_eth{1, 2, 3,  7};
  a_eth.unique();
  list_test_foo(a, a_eth);
}

TEST(list_sort, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.sort();
  // Assert
  std::list<int> a_eth{1, 2, 3};
  a_eth.sort();
  list_test_foo(a, a_eth);
}

TEST(list_sort, 2) {
  // Arrange
  s21::list<int> a{1};
  // Act
  a.sort();
  // Assert
  std::list<int> a_eth{1};
  a_eth.sort();
  list_test_foo(a, a_eth);
}

TEST(list_sort, 3) {
  // Arrange
  s21::list<int> a{3, 2, 7, 8, 1, -1};
  // Act
  a.sort();
  // Assert
  std::list<int> a_eth{3, 2, 7, 8, 1, -1};
  a_eth.sort();
  list_test_foo(a, a_eth);
}

TEST(list_emplace, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  auto iter = a.begin();

  iter = a.insert_many(iter, 3, 2, 7, 8, 1, -1);
  // Assert
  // ASSERT_EQ(*iter, -1)
  std::list<int> a_eth{3, 2, 7, 8, 1, -1, 1, 2, 3};
  list_test_foo(a, a_eth);
}

TEST(list_emplace_back, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.insert_many_back(3, 2, 7, 8, 1, -1);
  // Assert
  std::list<int> a_eth{1,2,3,3, 2, 7, 8, 1, -1};
  list_test_foo(a, a_eth);
}

TEST(list_emplace_front, 1) {
  // Arrange
  s21::list<int> a{1, 2, 3};
  // Act
  a.insert_many_front(3, 2);
  // Assert
  std::list<int> a_eth{3,2,1, 2, 3};
  list_test_foo(a, a_eth);
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


TEST(multiset_default_constructor, 1) {
  s21::multiset<int> a;
  // Assert
  std::multiset<int> a_eth;
  multiset_test_foo(a, a_eth);
}

TEST(multiset_parameterized_constructor, 1) {
  // Arrange
  // Act
  s21::multiset<int> a{1, 2, 3};
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  multiset_test_foo(a, a_eth);
}

TEST(multiset_parameterized_constructor, 2) {
  // Arrange
  // Act
  s21::multiset<int> a{1, 2, 3, 2};
  // Assert
  std::multiset<int> a_eth{1, 2, 3, 2};
  multiset_test_foo(a, a_eth);
}

TEST(multiset_copy_constructor, 1) {
  // Arrange
  s21::multiset<int> b{1, 2, 3};
  // Act
  s21::multiset<int> a(b);
  // Assert
  std::multiset<int> b_eth{1, 2, 3};
  std::multiset<int> a_eth(b_eth);
  multiset_test_foo(a, a_eth);
}

TEST(multiset_move_constructor, 1) {
  // Arrange
  s21::multiset<int> b{1, 2, 3, 3};
  // Act
  s21::multiset<int> a(std::move(b));
  // Assert
  std::multiset<int> b_eth{1, 2, 3, 3};
  std::multiset<int> a_eth(std::move(b_eth));
  multiset_test_foo(a, a_eth);
//   multiset_test_foo(b, b_eth);
}

TEST(multiset_eq_overriten_operator_r_value, 1) {
  // Arrange
  s21::multiset<int> a;
  s21::multiset<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::multiset<int> b_eth{1, 2, 3};
  std::multiset<int> a_eth;
  a_eth = std::move(b_eth);
  multiset_test_foo(a, a_eth);
//   multiset_test_foo(b, b_eth);
}

TEST(multiset_eq_overriten_operator_r_value, 2) {
  // Arrange
  s21::multiset<int> a{3, 2, 1};
  s21::multiset<int> b{1, 2, 3};
  // Act
  a = std::move(b);
  // Assert
  std::multiset<int> a_eth{3, 2, 1};
  std::multiset<int> b_eth{1, 2, 3};
  a_eth = std::move(b_eth);
  multiset_test_foo(a, a_eth);
//   multiset_test_foo(b, b_eth);
}

TEST(multiset_begin_iter, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
auto iter = *a.begin();
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  std::multiset<int>::iterator iter_eth = a_eth.begin();
  ASSERT_EQ(*iter, *iter_eth);
}


TEST(multiset_iterator_methods, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  auto iter = *a.begin();
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  for (; iter != a.end(); ++iter, ++iter_eth) {
    ASSERT_EQ(*iter, *iter_eth);
  }
}


TEST(multiset_empty, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3, 3};
  // Act
  // Assert
  std::multiset<int> a_eth{1, 2, 3, 3};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(multiset_empty, 2) {
  // Arrange
  s21::multiset<int> a;
  // Act
  // Assert
  std::multiset<int> a_eth;
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(multiset_empty, 3) {
  // Arrange
  s21::multiset<std::string> a{"1", "2", "3", "4"};
  // Act
  // Assert
  std::multiset<std::string> a_eth{"1", "2", "3", "4"};
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(multiset_size, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  ASSERT_EQ(a.size(), a_eth.size());
}

TEST(multiset_max_size, 1) {
  // Arrange
  s21::multiset<int> a;
  // Act
  // Assert
  std::multiset<int> a_eth;
  ASSERT_EQ(a.max_size(), 1000);
}

TEST(multiset_max_size, 2) {
  // Arrange
  s21::multiset<std::string> a;
  // Act
  // Assert
  std::multiset<std::string> a_eth;
  ASSERT_EQ(a.max_size(), 1000);
}

TEST(multiset_clear, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  a.clear();
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  a_eth.clear();
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}



TEST(multiset_clear, 3) {
  // Arrange
  s21::multiset<int> a{1, 2, 3, 4, 5};
  // Act
  a.clear();
  // Assert
  std::multiset<int> a_eth{1, 2, 3, 4, 5};
  a_eth.clear();
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(multiset_clear, 4) {
  // Arrange
  s21::multiset<int> a{5, 4, 3, 2, 1, 1};
  // Act
  a.clear();
  // Assert
  std::multiset<int> a_eth{5, 4, 3, 2, 1, 1};
  a_eth.clear();
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(multiset_clear, 5) {
  // Arrange
  s21::multiset<int> a;
  // Act
  a.clear();
  // Assert
  std::multiset<int> a_eth;
  a_eth.clear();
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(a.empty(), a_eth.empty());
}

TEST(multiset_insert, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  auto iter = *a.insert(7);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.insert(7);
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(multiset_insert, 2) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  auto iter = *a.insert(3);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.insert(3);
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(multiset_insert, 3) {
  // Arrange
  s21::multiset<int> a;
  // Act
  auto iter = *a.insert(7);
  // Assert
  std::multiset<int> a_eth;
  auto iter_eth = a_eth.insert(7);
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(multiset_insert, 4) {
  // Arrange
  s21::multiset<std::string> a{"1", "2", "3"};
  // Act
  auto iter = *a.insert("7");
  // Assert
  std::multiset<std::string> a_eth{"1", "2", "3"};
  auto iter_eth = a_eth.insert("7");
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(multiset_insert, 5) {
  // Arrange
  s21::multiset<std::string> a{"1", "2", "3"};
  // Act
  auto iter = *a.insert("2");
  // Assert
  std::multiset<std::string> a_eth{"1", "2", "3"};
  auto iter_eth = a_eth.insert("2");
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(*iter, *iter_eth);
}



TEST(multiset_erase, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  auto iter = a.begin();
  // Act
  a.erase(iter);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();
  a_eth.erase(iter_eth);
  multiset_test_foo(a, a_eth);
}



TEST(multiset_erase, 3) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  auto iter = a.begin();

  // Act
  a.erase(iter);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.begin();

  a_eth.erase(iter_eth);
  multiset_test_foo(a, a_eth);
}


TEST(multiset_erase, 7) {
  // Arrange
  s21::multiset<int> a{7, 6};
  auto iter = a.begin();

  // Act
  a.erase(iter);
  // Assert
  std::multiset<int> a_eth{7, 6};
  auto iter_eth = a_eth.begin();

  a_eth.erase(iter_eth);
  multiset_test_foo(a, a_eth);
}


TEST(multiset_swap, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  s21::multiset<int> b{4, 5};
  // Act
  a.swap(b);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  std::multiset<int> b_eth{4, 5};
  a_eth.swap(b_eth);
  multiset_test_foo(a, a_eth);
  multiset_test_foo(b, b_eth);
}

TEST(multiset_swap, 2) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  s21::multiset<int> b;
  // Act
  a.swap(b);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  std::multiset<int> b_eth;
  a_eth.swap(b_eth);
  multiset_test_foo(a, a_eth);
  multiset_test_foo(b, b_eth);
}

TEST(multiset_swap, 3) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  a.swap(a);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  a_eth.swap(a_eth);
  multiset_test_foo(a, a_eth);
}

// TEST(multiset_merge, 1) {
//   // Arrange
//   s21::multiset<int> a{1, 2, 3};
//   s21::multiset<int> b{4, 5};
//   // Act
//   a.merge(b);
//   // Assert
//   std::multiset<int> a_eth{1, 2, 3};
//   std::multiset<int> b_eth{4, 5};
//   a_eth.merge(b_eth);
//   multiset_test_foo(a, a_eth);
//   multiset_test_foo(b, b_eth);
// }

// TEST(multiset_merge, 2) {
//   // Arrange
//   s21::multiset<int> a;
//   s21::multiset<int> b{4, 5};
//   // Act
//   a.merge(b);
//   // Assert
//   std::multiset<int> a_eth;
//   std::multiset<int> b_eth{4, 5};
//   a_eth.merge(b_eth);
//   multiset_test_foo(a, a_eth);
//   multiset_test_foo(b, b_eth);
// }

TEST(multiset_merge, 3) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  s21::multiset<int> b;
  // Act
  a.merge(b);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  std::multiset<int> b_eth;
  a_eth.merge(b_eth);
  multiset_test_foo(a, a_eth);
  multiset_test_foo(b, b_eth);
}

TEST(multiset_merge, 4) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  s21::multiset<int> b{8, 5, 4 };
  // Act
  a.merge(b);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  std::multiset<int> b_eth{8, 5, 4};
  a_eth.merge(b_eth);
  multiset_test_foo(a, a_eth);
//   multiset_test_foo(b, b_eth);
}

TEST(multiset_merge, 5) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  s21::multiset<int> b{4, 5, 6};
  // Act
  a.merge(b);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  std::multiset<int> b_eth{4, 5, 6};
  a_eth.merge(b_eth);
  multiset_test_foo(a, a_eth);
//   multiset_test_foo(b, b_eth);
}

TEST(multiset_count, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  auto count = a.count(2);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto count_eth = a_eth.count(2);
//   multiset_test_foo(a, a_eth);
  ASSERT_EQ(count, count_eth);
}

TEST(multiset_count, 2) {
  // Arrange
  s21::multiset<int> a;
  // Act
  auto count = a.count(2);
  // Assert
  std::multiset<int> a_eth;
  auto count_eth = a_eth.count(2);
  multiset_test_foo(a, a_eth);
  ASSERT_EQ(count, count_eth);
}



TEST(multiset_find, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  auto iter = *a.find(1);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.find(1);
  ASSERT_EQ(*iter, *iter_eth);
}

TEST(multiset_find, 2) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  auto iter = *a.find(3);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  auto iter_eth = a_eth.find(3);
  ASSERT_EQ(*iter, *iter_eth);
}


TEST(multiset_contains, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  bool res = a.contains(2);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  bool res_eth = a.contains(2);
  ASSERT_EQ(res, res_eth);
}

TEST(multiset_contains, 2) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  bool res = a.contains(7);
  // Assert
  std::multiset<int> a_eth{1, 2, 3};
  bool res_eth = a.contains(7);
  ASSERT_EQ(res, res_eth);
}


TEST(multiset_emplace, 1) {
  // Arrange
  s21::multiset<int> a{1, 2, 3};
  // Act
  auto res = a.insert_many(4, 5, 6);
  // Assert
  std::multiset<int> a_eth{1, 2, 3, 4, 5, 6};
  std::vector<std::pair<int, bool>> res_eth{std::pair<int, bool>(4, true),
                                            std::pair<int, bool>(5, true),
                                            std::pair<int, bool>(6, true)};
  auto iter_eth = res_eth.begin();
  for (auto iter : res) {
    ASSERT_EQ(*(iter.first), (*iter_eth).first);
    ASSERT_EQ(iter.second, (*iter_eth).second);
    ++iter_eth;
  }
  multiset_test_foo(a, a_eth);
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

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
