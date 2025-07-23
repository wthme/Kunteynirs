#include <initializer_list>
#include <string>

namespace s21 {

template <class T, size_t N>
class array {
  using const_ref = const T&;
  using ref = T&;
  using iterator = T*;
  using const_iterator = const T*;

 private:
  size_t cap;
  T* arr_pntr;
  size_t arsize;

 public:
  array();
  array(std::initializer_list<T> const& init_elements);
  array(array& copied_array);
  array(array&& mooved_array);
  ~array();

  array<T, N>& operator=(array<T, N>&& mooved_array);
  ref operator[](size_t pos);
  ref at(size_t pos);

  const_ref front() { return *arr_pntr; };
  const_ref back() { return *(end() - 1); };
  iterator data() { return arr_pntr; };
  iterator begin() { return arr_pntr; };
  iterator end() { return arr_pntr + arsize; };

  bool empty() { return !(arsize > 0); };
  size_t size() { return this->arsize; };
  size_t max_size() { return this->cap; };

  void swap(array<T, N>& swapping_array);
  void fill(const T& value);
};
}  // namespace s21