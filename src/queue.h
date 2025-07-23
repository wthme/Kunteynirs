#include <initializer_list>
#include <iostream>

namespace s21 {

template <class T>
class Queue {
  using size_t = unsigned long;

 private:
  size_t size;

 public:
  struct Node {
    Node *next{nullptr};
    T elem;
  };

 private:
  Node *root;
  Node *end_pntr;

 public:
  Queue();
  Queue(std::initializer_list<T> const &items);
  Queue(const Queue<T> &other);
  Queue(Queue<T> &&other);
  Queue<T> &operator=(Queue<T> &&other);
  ~Queue();

  size_t get_size();
  bool empty();

  void push(T new_elem);
  void pop();
  void swap(Queue<T> &other);
  const T &front();
  const T &back();

  void print();

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (this->push(args), ...);
  }
};
};  // namespace s21