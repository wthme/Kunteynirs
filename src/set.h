#include <initializer_list>
#include <iostream>
#include <vector>
#include <set>
#include <string>

namespace s21 {
template <class T>   

class set {
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

                    Btree * add_pos(T& new_elem);

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

      using insert_list = std::vector<std::pair<typename set<T>::Btree, bool>>;
      using para = typename std::pair <typename set<T> :: Btree, bool>;
      using iter = typename set<T>::Btree;

public:
            static const size_t Max_size = 1000;
            size_t ssize;
            Btree * root;
            Btree * fuck_root;

  public:
      set();
      set(std::initializer_list<T> const & init_elems); 
      set(const set<T> & copyng_set);
      set(set<T> && mooving_set);
      ~set();
      set<T> & operator=(set<T>&& mooving_set);

      void add(const T& value);

      Btree * begin(){
            Btree * begin;
            if (size() == 0){begin = fuck_root;}
            else {begin = root->get_down();
                  begin->status = true;}
            return begin;};

      Btree * end(){return fuck_root;};
            
      Btree * cbegin() const{
            Btree * begin;
            if (ssize == 0){begin = fuck_root;}
            else {begin = root->get_down(); begin->status = true;}
            return begin;};

      Btree * cend() const{return fuck_root;};

      bool empty(){return (ssize == 0);};
      size_t size(){return ssize;};
      size_t max_size(){return Max_size;};

      void clear();
      para insert(const T& value);
      void erase(typename set<T>:: Btree * pos);
      void swap(set<T>& swapping_set);
      void merge(set<T>& another_set);
      typename set<T>::Btree * find (const T& value) const;
      bool contains(const T& value) const;


void unpack (T& value , insert_list vector){
      T const insert_value = value;
      const para vstavka = insert(insert_value);
      vector.push_back(vstavka);
}

template <typename ... Args>
      insert_list insert_many(Args&&... args){ 
           insert_list result;
            (unpack(args,result), ... );
      return result;
      }; // здесь распаковка};     
};
}  // namespace s21
