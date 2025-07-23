#include "stack.h"
#include <initializer_list>

template <typename T>
using const_ref = const T &;

template <typename T>
using ref = T &;

template <typename T>
using stek = s21::stack<int>;

template <class T>
s21::stack<T>::stack() {
  occup = 0;
  cap = default_cap;
  arr_pntr = new T[cap];
}

template <class T>
s21::stack<T>::stack(size_t set_up_capacity) {
  occup = 0;
  cap = set_up_capacity;
  arr_pntr = new T[cap];
  std::cout << "set cap constr\n";
}

template <class T>
s21::stack<T>::stack(std::initializer_list<T> const &elements) {
  occup = 0;
  cap = default_cap;
  arr_pntr = new T[cap];
  for (auto it = elements.begin(); it != elements.end(); ++it) {
    push(*it);
  }
  std::cout << "init_list constr\n";
}

template <class T>
s21::stack<T>::stack(
    stack<T> &copyng_stack) {  // не работает доделай кондишнл джамп
  cap = copyng_stack.cap;
  occup = 0;
  T *new_arr = new T[cap];
  arr_pntr = new_arr;

  size_t temp_size = copyng_stack.size();

  T temp_arr[temp_size];

  for (size_t i = temp_size; i != 0; --i) {
    temp_arr[i - 1] = copyng_stack.top();
    copyng_stack.pop();
  }

  for (size_t i = 0; i < temp_size; ++i) {
    copyng_stack.push(temp_arr[i]);
    push(temp_arr[i]);
    std::cout << temp_arr[i];
  }

  std::cout << "copy constr\n";
}

template <class T>
s21::stack<T>::stack(s21::stack<T> &&mooving_stack) {
  occup = 0;
  arr_pntr = nullptr;
  cap = 0;
  swap(mooving_stack);
  std::cout << "mooving constr\n";
}

template <class T>
s21::stack<T>::~stack() {
  while (!empty()) {
    this->pop();
  }
  if (arr_pntr != nullptr) {
    delete[] arr_pntr;
  }
  occup = 0;
  arr_pntr = nullptr;
  cap = 0;
}

template <class T>
s21::stack<T> &s21::stack<T>::operator=(stack<T> &&mooving_stack) {
  swap(mooving_stack);
  std::cout << "ravno operator = mooving moove\n";
  mooving_stack.~stack();

  return *this;
}

template <class T>
const_ref<T> s21::stack<T>::top() {
  if (size() > 0) {
    return *arr_pntr;
  } else
    throw std::out_of_range("empty stack\n");
}

template <class T>
void s21::stack<T>::push(const_ref element) {
  if (size() < cap) {
    if (empty()) {
      *arr_pntr = element;
      occup++;
    } else if (size() > 0) {
      arr_pntr++;
      *arr_pntr = element;
      occup++;
    }
  } else
    throw std::runtime_error("stack overflow\n");
}

template <class T>
void s21::stack<T>::pop() {
  if (size() > 1) {
    occup--;
    arr_pntr--;
  } else if (size() == 1) {
    occup--;
  } else
    throw std::out_of_range("пустой стек !\n");
}

template <class T>
void s21::stack<T>::swap(stack<T> &another_stack) {
  std::swap(arr_pntr, another_stack.arr_pntr);
  std::swap(occup, another_stack.occup);
  std::swap(cap, another_stack.cap);
}

template class s21::stack<int>;
template class s21::stack<double>;
template class s21::stack<float>;
template class s21::stack<char>;
