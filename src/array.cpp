#include "array.h"

#include <iostream>

template <class T, size_t N>
s21::array<T, N>::array() {
  arsize = N;
  arr_pntr = new T[N + 1];
  cap = N;
}

template <class T, size_t N>
s21::array<T, N>::array(std::initializer_list<T> const& init_elements) {
  arr_pntr = nullptr;

  if (init_elements.size() <= N) {
    cap = N;
    arsize = init_elements.size();
    T* new_arr = new T[N + 1];

    int count = 0;
    for (auto it = init_elements.begin(); it != init_elements.end(); ++it) {
      new_arr[count] = *it;
      ++count;
    }
    arr_pntr = new_arr;
  }

  else
    throw std::out_of_range("недопустимое число элементов");
}

template <class T, size_t N>
s21::array<T, N>::array(s21::array<T, N>& copied_array) {
  cap = copied_array.cap;
  arsize = copied_array.arsize;

  T* new_arr = new T[cap + 1];
  arr_pntr = new_arr;

  T* it = begin();
  for (T* iter = copied_array.begin(); iter != copied_array.end(); ++iter) {
    *it = *iter;
    it++;
  }
}

template <class T, size_t N>
s21::array<T, N>::array(s21::array<T, N>&& mooved_array) {
  cap = 0;
  arr_pntr = nullptr;
  arsize = 0;
  swap(mooved_array);
}

template <class T, size_t N>
s21::array<T, N>::~array() {
  if (arr_pntr != nullptr) {
    delete[] arr_pntr;
  }
  arsize = 0;
  cap = 0;
  arr_pntr = nullptr;
}

template <class T, size_t N>
s21::array<T, N>& s21::array<T, N>::operator=(array<T, N>&& mooved_array) {
  swap(mooved_array);
  mooved_array.~array();
  return *this;
}

template <class T, size_t N>
T& s21::array<T, N>::operator[](size_t pos) {
  if (pos >= 0 && pos < cap) {
    return *(data() + pos);
  } else
    throw std::out_of_range("wrongg ind");
}

template <class T, size_t N>
T& s21::array<T, N>::at(size_t pos) {
  if (pos >= 0 && pos < cap) {
    return *(data() + pos);
  } else
    throw std::out_of_range(" wrong index bro");
}

template <class T, size_t N>
void s21::array<T, N>::swap(array<T, N>& mooved_array) {
  std::swap(arr_pntr, mooved_array.arr_pntr);
  std::swap(cap, mooved_array.cap);
  std::swap(arsize, mooved_array.arsize);
}

template <class T, size_t N>
void s21::array<T, N>::fill(const T& value) {
  for (T* it = begin(); it != end(); ++it) {
    *it = value;
  }
}

template class s21::array<int, 0>;
template class s21::array<int, 1>;
template class s21::array<int, 5>;
template class s21::array<int, 7>;
template class s21::array<double, 10>;
template class s21::array<int, 3>;
template class s21::array<std::string, 1>;
