#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T>
class vector {
  static const size_t Max_size = 228;
  size_t cap;
  size_t vsize;
  T* arr;

  using vec = s21::vector<T>;
  using ref = T&;
  using const_ref = const T&;
  using iterator = T*;
  using const_iterator = const T*;

 public:
  vector();
  vector(size_t capacity);
  vector(std::initializer_list<T> const& cords);
  vector(const vector<T>& copied_vec);
  vector(vector<T>&& mooved_vector);
  ~vector();
  vector<T>& operator=(vector<T>&& mooved_vector);

  T& at(size_t pos);
  T& operator[](size_t pos);
  const_ref front() { return arr[0]; };
  const_ref back() { return arr[vsize - 1]; };
  T* data() { return arr; };

  iterator begin() { return arr; };
  iterator end() { return arr + vsize; };

  bool empty();
  size_t size() { return vsize; };
  size_t max_size() { return Max_size; };
  void reserve(size_t capacity);
  size_t capacity() { return cap; };
  void shrink_to_fit() { reserve(vsize); }
  void clear() { vsize = 0; };

  T* insert(iterator pos, const_ref element);
  void erase(iterator pos);
  void push_back(const T& new_element);
  void pop_back();
  void swap(vector<T>& other);  // доделатьg++

  // доп методы

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    reserve(3 * cap);
    (this->push_back(args), ...);
    // shrink_to_fit();
  };

  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args) {
    if (pos >= begin() && pos <= end()) {
      vector<T> obrubok = vector(pos - begin());
      obrubok.clear();
      for (iterator it = pos; it != end(); ++it) {
        obrubok.push_back(*it);
      }  // обрубаем вектор
      for (iterator it = end(); it != pos; --it)
        pop_back();                  // перемещаем указатель
      (this->push_back(args), ...);  // добавляем в конец мультипуш
      for (iterator it = obrubok.begin(); it != obrubok.end(); ++it)
        this->push_back(*it);  // добавляем обрубок

      iterator resultat = end() - obrubok.size();  //

      return resultat;
    }

    else
      throw std::out_of_range("wrongg index");
  }

};  //     class vector
};  //   namespace s21
