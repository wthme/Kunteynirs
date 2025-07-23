#include <initializer_list>
#include <iostream>
#include "Btree.h"
#include <vector>
#include <set>
#include <string>

namespace s21 {
template <class T>   

class multiset {

    class Btree{
                  public:
                      Btree * parent;
                      Btree * left;
                      Btree * right;
                      T data{0};
                      bool status;

                    Btree(const T & elem) : parent(nullptr), left {nullptr}, right {nullptr}, status(false), data(elem){};
                    Btree():parent(nullptr), left {nullptr}, right {nullptr}, status(false){};
                   ~Btree(){};

                    Btree & operator = (Btree iter){ 
                      parent = iter.parent;
                      data = iter.data;
                      left = iter.left;
                      right = iter.right;
                      status = iter.status;
                      return *this;}

                    Btree * operator = (Btree * iter){ 
                      data = iter->data;
                      left = iter->left;
                      right = iter->right;
                      parent = iter->parent;
                      status = iter->status;
                      return this;}

                    T & operator *() {return data;};
                    bool operator !=(Btree & other){return ((data != other.data)  || (status != other.status));};
                    bool operator ==(Btree & other){return ((data == other.data)  && (status == other.status));};
                    bool operator !=(Btree * other){return ((data != other->data) || (status != other->status));};
                    bool operator ==(Btree * other){return ((data == other->data)  && (status == other->status));};

                    Btree & operator ++(){
                      Btree * next_node = appnext();
                      *this = *next_node;
                      return *this;};

                    Btree & operator ++(int){
                      Btree * next_node = appnext();
                      *this = next_node;
                      return *this;};

                    Btree * add_all_pos(T& new_elem);

                    void ldbond(Btree * other_node){
                      left = other_node;
                      other_node->parent = this;};

                    void rdbond(Btree * node){
                      right = node;
                      node->parent = this;};

                    Btree * ldown(){return left;}

                    Btree * rdown(){return right;}

                    Btree * up(){return parent;}

                    Btree * get_down(){
                          Btree * res = this;
                          while(res->left != nullptr){
                          res = res->ldown();}
                      return res;}

                    bool check_right();
                    bool status_check();
                    Btree * next();
                    Btree * appnext();
                    bool onechild(){return (left == nullptr && right != nullptr) || (left != nullptr && right == nullptr);};
                    bool twochild(){return (left!=nullptr && right != nullptr);};
                    bool free(){return (left==nullptr && right == nullptr);};
                    void destroy_list();
                    Btree * destroy_branch();  // возвращает ноду под удаленной
                    void unbond_list(); 
                    void unbond_branch();
                    Btree * destroy_hub();
                    void take_pntrs(Btree * other_node);
          }; 

using para = typename std::pair <typename multiset<T> :: Btree, bool>;
using insert_list = std::vector<std::pair<typename multiset<T>::Btree, bool>>;
using range = std::pair <typename multiset<T>::Btree, typename multiset<T>::Btree>;

  public:
      static const size_t Max_size = 1000;
      size_t multisize;
      Btree * root;
      Btree * fuck_root;

      multiset();
      multiset(std::initializer_list<T> const & init_elems); 
      multiset(const multiset<T> & copyng_set);
      multiset(multiset<T> && mooving_set);
      ~multiset();
      multiset<T>& operator = (multiset<T>&& mooving_set);

    void add(const T& value);

      Btree * begin(){
            Btree * begin;
            if (size() == 0){begin = fuck_root;}
            else {begin = root->get_down();
                  begin->status = true;}
            return begin;};

      Btree * end(){return fuck_root;};

      Btree * cbegin() const {
            Btree * begin;
            if (multisize == 0){begin = fuck_root;}
            else {begin = root->get_down();
                  begin->status = true;}
            return begin;};

      Btree * cend() const{return fuck_root;};

      bool empty(){return (multisize == 0);};
      size_t size() const {return multisize;} ;
      size_t max_size()const {return Max_size;};
      void clear();
      Btree * insert(const T& value);
      void erase(Btree * pos);
      void swap(multiset<T> & swapping_set);
      void merge(multiset<T> & another_set);
      size_t count(const T& value) const;
      Btree * find (const T& value) const;
      bool contains(const T& value) const;
   
void unpack (T& value , insert_list vector){
      T const insert_value = value;
      para vstavka;
      vstavka.first = insert(insert_value);
      vstavka.second = true;
      vector.push_back(vstavka);}

template <typename ... Args>
      insert_list insert_many(Args&&... args){ 
      insert_list result;
      (unpack(args,result), ... );
      return result;}; // здесь распаковка};     
};
}