#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <queue>

#include "queue.h"
#include "vector.h"

using s21::Queue;
using std::queue;

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
