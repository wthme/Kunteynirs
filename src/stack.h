#include <iostream>

namespace s21 {
template <class T>

class stack {
  using ref = T&;
  using const_ref = const T&;

 private:
  static const size_t default_cap = 25;
  size_t cap;
  size_t occup;
  T* arr_pntr;

 public:
  stack();
  stack(size_t set_up_capacity);
  stack(std::initializer_list<T> const& elements);
  stack(stack<T>& copyng_stack);
  stack(stack<T>&& mooving_stack);
  ~stack();

  stack<T>& operator=(stack<T>&& mooving_stack);

  const_ref top();
  bool empty() { return occup == 0; };
  size_t size() { return occup; };

  void push(const_ref new_elem);
  void pop();
  void swap(stack<T>& other);

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(args), ...);
  };
};
};  // namespace s21
