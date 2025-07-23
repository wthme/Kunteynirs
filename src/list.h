#include <iostream>
#include <string>

namespace s21 {
template <class T>
class list {
 public:
  class ListIterator {
   public:
    ListIterator* prev;
    ListIterator* next;
    T data{0};
    ListIterator(const T& element);
    ListIterator() {
      next = nullptr;
      prev = nullptr;
    };
    ~ListIterator(){};
    T& operator*() { return data; };
    ListIterator& operator++() {
      *this = *next;
      return *this;
    };

    ListIterator& operator--() {
      *this = *prev;
      return *this;
    };

    bool operator==(ListIterator it) { return (data == it.data); };
    bool operator!=(ListIterator it) { return data != it.data; };
    void rbond(ListIterator* right) {
      this->next = right;
      right->prev = this;
    }
    void lbond(ListIterator* left) {
      this->prev = left;
      left->next = this;
    }
    void destroy();
    void stealth();
  };

 protected:
  static const size_t Maxsize = 1000;
  ListIterator* root;
  ListIterator* lend;
  size_t lsize;

 public:
  list();
  list(size_t n);
  list(std::initializer_list<T> const& elems);
  list(list<T>& copyng_list);
  list(list<T>&& mooving_list);
  ~list();
  list<T>& operator=(list<T>&& mooving_list);
  const T& front() { return root->data; };
  const T& back() { return lend->prev->data; };
  ListIterator& begin() { return *root; };
  ListIterator& end() { return *lend; };
  bool empty() { return lsize == 0; };
  size_t size() { return lsize; };
  size_t max_size() { return Maxsize; };
  void clear();
  ListIterator insert(ListIterator* pos, const T& value);
  void erase(ListIterator* pos);
  void push_back(const T& new_elem);
  void pop_back();
  void push_front(const T& new_elem);
  void pop_front();
  void swap(list<T>& swapping_list);
  void merge(list<T>& merging_list);
  void splice(ListIterator* pos, list<T>& splicing_list);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  ListIterator insert_many(const ListIterator pos, Args&&... args) {
    (insert(pos.next->prev, args), ...);
    return pos;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push_back(args), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    list<T> temp_list = list();
    (temp_list.push_back(args), ...);
    temp_list.merge(*this);
    this->~list();
    new (this) list(std::move(temp_list));
  }
};
}  // namespace s21
