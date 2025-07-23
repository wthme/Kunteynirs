#include "queue.h"

template <class T>
s21::Queue<T>::Queue() {
  size = 0;
  end_pntr = nullptr;
  root = new Node;
}

template <class T>
s21::Queue<T>::Queue(std::initializer_list<T> const &items) {
  size = 0;
  root = new Node();
  end_pntr = nullptr;
  for (auto it = items.begin(); it != items.end(); ++it) this->push(*it);
}

template <class T>
s21::Queue<T>::Queue(const s21::Queue<T> &other) {
  size = 0;
  root = new Node();
  end_pntr = nullptr;

  Node *pntr = other.root->next;
  for (int i = 0; i < other.size; ++i) {
    this->push(pntr->elem);
    pntr = pntr->next;
  }
}

template <class T>
s21::Queue<T>::Queue(s21::Queue<T> &&other) {
  size = other.size;

  root = std::move(other.root);
  end_pntr = std::move(other.end_pntr);

  other.size = 0;
  other.root = nullptr;
  other.end_pntr = nullptr;
}

template <typename T>
s21::Queue<T> &s21::Queue<T>::operator=(s21::Queue<T> &&other) {
  this->~Queue();

  new (this) s21::Queue(std::move(other));
  return *this;
}

template <class T>
s21::Queue<T>::~Queue() {
  while (size) {
    this->pop();
  }
  delete root;
}

template <class T>
size_t s21::Queue<T>::get_size() {
  return size;
}

template <class T>
bool s21::Queue<T>::empty() {
  bool res{false};
  if (size == 0) res = true;
  return res;
}

template <typename T>
void s21::Queue<T>::push(T new_elem) {
  if (size == 0) {
    Node *first = new Node;

    root->next = first;
    end_pntr = first;
    end_pntr->elem = new_elem;
    size++;
  } else {
    Node *new_node{new Node};
    end_pntr->next = new_node;
    end_pntr = new_node;
    end_pntr->elem = new_elem;
    size++;
  }
}

template <typename T>
void s21::Queue<T>::pop() {
  if (size == 1) {
    end_pntr = nullptr;
    delete root->next;
    --size;
  } else if (size > 1) {
    Node *new_root = root->next->next;
    delete root->next;
    root->next = new_root;
    --size;
  } else
    throw std::runtime_error("empty");
}

template <typename T>
void s21::Queue<T>::swap(Queue<T> &other) {
  std::swap(this->size, other.size);
  std::swap(this->root, other.root);
  std::swap(this->end_pntr, other.end_pntr);
}

template <typename T>
const T &s21::Queue<T>::front() {
  if (size > 0) {
    const T &res = root->next->elem;
    return res;
  } else
    throw std::runtime_error("empty queue");
}

template <typename T>
const T &s21::Queue<T>::back() {
    const T &res = end_pntr->elem;
    return res;
}

// template <typename T>
// void s21::Queue<T>::print() {
//   while (size) {
//     std::cout << this->front();
//     this->pop();
//   }
// }

template class s21::Queue<int>;  // инстанцирование шаблонов для тестов
template class s21::Queue<double>;
template class s21::Queue<float>;
