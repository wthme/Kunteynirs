#include "vector.h"

#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>


template <class T>
using iterator = T*;

template <class T>
using ref = T&;

template <class T>
using vec = typename s21::vector<T>;  // type-id is A<T>::U

template <class T>
s21::vector<T>::vector() {
  arr = nullptr;
  vsize = 0;
  cap = 0;  // cap должен быть на 1 меньше массива чтобы было ясно где конец.
}

template <class T>
s21::vector<T>::vector(size_t capacity) {
  if (capacity <= Max_size) {
    cap = capacity;
    arr = new T[cap + 1];
    vsize = capacity;
  } else
    throw std::runtime_error("превышен максимальный размер");
}

template <class T>
s21::vector<T>::vector(const s21::vector<T>& copied_vec) {
  cap = copied_vec.vsize;
  vsize = cap;

  T* new_arr = new T[cap + 1];

  for (int i = 0; i < vsize; ++i) {
    new_arr[i] = copied_vec.arr[i];
  }
  arr = new_arr;
}

template <class T>
s21::vector<T>::vector(s21::vector<T>&& mooved_vector) {
  cap = mooved_vector.cap;
  vsize = mooved_vector.vsize;
  arr = mooved_vector.arr;

  mooved_vector.arr = nullptr;
  mooved_vector.vsize = 0;
  mooved_vector.cap = 0;
}

template <class T>
s21::vector<T>& s21::vector<T>::operator=(s21::vector<T>&& mooved_vector) {
  std::swap(arr, mooved_vector.arr);
  std::swap(cap, mooved_vector.cap);
  std::swap(vsize, mooved_vector.vsize);

  mooved_vector.~vector();

  // s21::vector<T> * new_vector = new s21::vector<T>(std::move(mooved_vector));
  // s21::vector<T> & ref_on_vec = * new_vector;

  return *this;
}

template <class T>
s21::vector<T>::vector(std::initializer_list<T> const& cords) {
  vsize = cords.size();
  cap = vsize;
  arr = new T[cap + 1];

  int count = 0;
  for (auto it = cords.begin(); it != cords.end(); ++it) {
    arr[count] = *it;
    count++;
  }
}

template <class T>
s21::vector<T>::~vector() {
  if (arr != nullptr) {
    delete[] arr;
    arr = nullptr;
    vsize = 0;
    cap = 0;
  }
}

template <class T>
void s21::vector<T>::reserve(size_t capacity) {
  if (capacity >= vsize) {
    s21::vector<T> new_vector = s21::vector<T>(capacity);
    new_vector.clear();

    for (iterator it = begin(); it != end(); ++it) {
      new_vector.push_back(*it);
    }

    std::swap(arr, new_vector.arr);
    std::swap(cap, new_vector.cap);
  }
}

template <class T>
T& s21::vector<T>::at(size_t pos) {
  if (pos >= 0 && pos < vsize) {
    T* element = this->begin() + pos;
    T& ref = *element;
    return ref;
  } else
    throw std::out_of_range("неправиьный индекс");
}

template <typename T>
ref<T> s21::vector<T>::operator[](size_t pos) {
  if (pos >= 0 && pos < vsize) {
    return this->at(pos);
  } else
    throw std::out_of_range("wrong index");
}

template <class T>
bool s21::vector<T>::empty() {
  bool res;
  if (vsize == 0)
    res = true;
  else if (vsize < cap)
    res = true;
  else
    res = false;
  return res;
}

template <typename T>
iterator<T> s21::vector<T>::insert(iterator pos, const_ref new_element) {
  if (pos >= begin() &&
      pos <= end()) {  // диапазон включая последний пустой элемент
    if (pos == end())
      push_back(new_element);  // вставка в конец это пуш

    else {
      vector<T> obrubok = vector(pos - begin());
      obrubok.clear();

      for (iterator it = pos; it != end(); ++it) {
        obrubok.push_back(*it);
      }
      *pos = new_element;  // кладем куда надо

      for (iterator it = end() - 1; it != pos; --it) {  //смещаем указатель
        pop_back();
      }
      for (iterator it = obrubok.begin(); it != obrubok.end();
           ++it) {  // пушим обрубок
        push_back(*it);
      }
      return pos;
    }
  } else
    throw std::out_of_range("out of range");
  return nullptr;
}

template <typename T>
void s21::vector<T>::erase(iterator pos) {
  if (pos < this->end()) {
    s21::vector<T> temp;

    for (iterator it = begin(); it != pos; ++it) {
      temp.push_back(*it);
    }

    for (iterator it = pos + 1; it != end(); ++it) temp.push_back(*it);

    std::swap(arr, temp.arr);
    std::swap(cap, temp.cap);
    std::swap(vsize, temp.vsize);
  } else
    throw std::out_of_range("out of range");
}

template <typename T>
void s21::vector<T>::push_back(const T& new_element) {
  if (cap == 0) {
    this->reserve(1);
  }

  else if (vsize == cap) {
    this->reserve(cap * 2);
  }

  arr[vsize] =
      new_element;  // arr[vsize] это следующий за последним так как счет с нуля
  vsize++;
}

template <typename T>
void s21::vector<T>::pop_back() {
  if (vsize > 0) {
    vsize--;
  } else
    throw std::out_of_range("пусто wrong index");
}

template <typename T>
void s21::vector<T>::swap(s21::vector<T>& other) {
  std::swap(this->arr, other.arr);
  std::swap(this->vsize, other.vsize);
  std::swap(this->cap, other.cap);
}

template <typename T>
void print(T vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec.at(i) << std::endl;
  }
}

template class s21::vector<int>;  // инстанцирование шаблонов для тестов
template class s21::vector<double>;
template class s21::vector<float>;
template class s21::vector<char>;
template class s21::vector<std::string>;
// template class s21::vector<std::pair < Btree<int>::iterator, bool> >;






