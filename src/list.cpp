#include "list.h"
#include <signal.h>
#include <initializer_list>
#include <list>


template <class T>
s21::list<T>::list() {
  lsize = 0;
  s21::list<T>::ListIterator* new_node = new ListIterator();
  lend = new_node;
  root = new_node;
}

template <class T>
s21::list<T>::list(size_t n) {
  if (n <= max_size()) {
    lsize = n;
    s21::list<T>::ListIterator* empty_node = new ListIterator();
    lend = empty_node;
    root = empty_node;

    for (int i = 0; i < n; ++i) {
      ListIterator* new_root = new ListIterator();
      new_root->rbond(root);
      root = new_root;
    }
  } else
    throw std::runtime_error("to much");
}

template <class T>
s21::list<T>::list(std::initializer_list<T> const& items) {
  lsize = 0;
  s21::list<T>::ListIterator* new_node = new ListIterator();
  lend = new_node;
  root = new_node;
  for (auto it = items.begin(); it != items.end(); ++it) push_back(*it);
}

template <class T>
s21::list<T>::list(s21::list<T>& copyng_list) {
  lsize = 0;
  s21::list<T>::ListIterator* new_node = new ListIterator();
  lend = new_node;
  root = new_node;
  for (auto it = copyng_list.begin(); it != copyng_list.end(); ++it)
    push_back(*it);
}

template <class T>
s21::list<T>::list(s21::list<T>&& mooving_list) {
  lsize = 0;
  lend = nullptr;
  root = nullptr;
  swap(mooving_list);
}

template <class T>
s21::list<T>::~list() {
  clear();
  delete lend;
}

template <class T>
s21::list<T>& s21::list<T>::operator=(s21::list<T>&& mooving_list) {
  this->~list();
  new (this) list(std::move(mooving_list));
  return *this;
}

template <class T>
void s21::list<T>::clear() {
  while (!empty()) {
    ListIterator* new_root = root->next;
    delete root;
    root = new_root;
    lsize--;
  }
}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::insert(ListIterator* pos,
                                                         const T& value) {
  ListIterator res;
  if (size() == 0) {
    push_back(value);
  } else if (*pos == begin()) {
    push_front(value);
    res = begin();
  } else if (*pos == end()) {
    push_back(value);
    res = *(lend->prev);
  } else {
    ListIterator* prev_node = pos->prev;
    ListIterator* new_node = new ListIterator(value);
    new_node->lbond(prev_node);
    new_node->rbond(pos);
    res = *new_node;
    lsize++;
  }
  return res;
}

template <typename T>
void s21::list<T>::erase(ListIterator* pos) {
  if (*pos == begin()) {
    root = pos->next;
    delete pos;
  } else {
    (*pos).destroy();
  }
  lsize--;
}

template <typename T>
void s21::list<T>::push_back(const T& new_elem) {
  ListIterator* new_node = new ListIterator(new_elem);
  if (empty()) {
    new_node->rbond(lend);
    root = new_node;
  } else {
    ListIterator* pre_last = end().prev;
    new_node->lbond(pre_last);
    new_node->rbond(lend);
  }
  lsize++;
}

template <typename T>
void s21::list<T>::pop_back() {
  if (!empty()) {
    erase(end().prev);
  } else
    throw std::out_of_range("пусто!");
}

template <typename T>
void s21::list<T>::push_front(const T& new_elem) {
  ListIterator* new_node = new ListIterator(new_elem);
  new_node->rbond(root);
  root = new_node;
  lsize++;
}

template <typename T>
void s21::list<T>::pop_front() {
  if (!empty()) {
    erase(begin().next->prev);
  } else
    throw std::out_of_range("пусто!");
}

template <typename T>
void s21::list<T>::swap(list<T>& swapping_list) {
  std::swap(lsize, swapping_list.lsize);
  std::swap(root, swapping_list.root);
  std::swap(lend, swapping_list.lend);
}

template <typename T>
void s21::list<T>::merge(s21::list<T>& merging_list) {
  if (size() == 0) {
    this->~list();
    new (this) list(std::move(merging_list));
  }

  else if (merging_list.size() > 0) {
    lsize = lsize + merging_list.size();
    ListIterator* last = lend->prev;
    last->rbond(merging_list.root);
    delete lend;
    lend = merging_list.lend;
    merging_list.lsize = 0;
    merging_list.root = nullptr;
    merging_list.lend = nullptr;
  }
}

template <typename T>
void s21::list<T>::splice(ListIterator* pos, list<T>& splicing_list) {
  if (size() == 0) {
    this->~list();
    new (this) list(splicing_list);
  } else if (*pos == begin()) {
    (splicing_list.lend->prev)->rbond(root);
    root = splicing_list.root;
    lsize = splicing_list.size() + lsize;
    splicing_list.lsize = 0;
  } else if (*pos == end()) {
    merge(splicing_list);
    // splicing_list.lsize = 0;
  }

  else {
    if (splicing_list.size() > 0) {
      lsize = splicing_list.size() + lsize;
      splicing_list.lsize = 0;
      ListIterator* aim = pos->prev;
      ListIterator* last = splicing_list.lend->prev;
      pos->lbond(last);
      aim->rbond(splicing_list.root);
    }
  }
}

template <typename T>
void s21::list<T>::reverse() {
  list dop_list = list();  // дедовский метод с копированием моветон

  for (ListIterator it = begin(); it != end(); ++it) dop_list.push_front(*it);
  this->~list();
  new (this) list(std::move(dop_list));
}

template <typename T>
void s21::list<T>::unique() {
  sort();
  ListIterator check = *begin();
  for (s21::list<T>::ListIterator it = *(begin().next); it != end(); ++it) {
    if (*it == *check) {
      erase(it.prev);
    }
    if (*it > *check) *check = *it;
  }
}

template <typename T>
void s21::list<T>::sort() {
  list<T> temp_list = list();  // дедоовский способ))
  size_t razm = lsize;

  T min_element = *begin();
  T max_element = *begin();

  for (size_t i = 0; i != razm; ++i) {
    for (ListIterator it = begin(); it != end(); ++it) {
      if (*it >= max_element) {
        temp_list.push_back(*it);
        max_element = *it;
        erase(it.next->prev);
        break;
      }

      else if (*it <= min_element) {
        temp_list.push_front(*it);
        min_element = *it;
        erase(it.next->prev);
        break;
      }

      else {
        for (ListIterator iter = temp_list.begin(); iter != temp_list.end();
             ++iter) {
          if (**(iter.next) >= *it) {
            temp_list.insert(iter.next, *it);
            erase(it.next->prev);
            break;
          }
        }
      }
    }
  }

  this->~list();
  new (this) list(std::move(temp_list));
}

template <class T>
s21::list<T>::ListIterator::ListIterator(const T& element) {
  prev = nullptr;
  next = nullptr;
  data = element;
}

template <class T>
void s21::list<T>::ListIterator::destroy() {
  ListIterator* left = prev;
  ListIterator* right = next;
  left->rbond(right);
  delete this;
}

template <class T>
void s21::list<T>::ListIterator::stealth() {
  ListIterator* left = prev;
  ListIterator* right = next;
  left->rbond(right);
}

template class s21::list<int>; 
template class s21::list<double>;
template class s21::list<float>;
template class s21::list<char>;
template class s21::list<std::string>;