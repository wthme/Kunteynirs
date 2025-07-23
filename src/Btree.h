#include <initializer_list>
#include <string>
#include <iostream>

template <class T>
class Btree {
            public:
                    Btree() {root = new Btree<T>::iterator();};
                    ~Btree() {delete root;};   
                         
            class iterator{
                  public:
                      iterator * parent;
                      iterator * left;
                      iterator * right;
                      bool status;
                      T data{0};

                    iterator(const T & elem) : parent(nullptr), left {nullptr}, right {nullptr}, status(false),data(elem){};
                    iterator() : parent(nullptr), left {nullptr}, right {nullptr}, status(false){};
                    ~iterator(){};

                    iterator  operator = (iterator iter){ 
                      parent = iter.parent;
                      data = iter.data;
                      left = iter.left;
                      right = iter.right;
                      status = iter.status;
                           return *this;}

                    iterator *  operator = (iterator* iter){ 
                      data = iter->data;
                      left = iter->left;
                      right = iter->right;
                      parent = iter->parent;
                      status = iter->status;
                           return this;}


                    T & operator *(){ return data;};
                    bool operator !=(iterator&other){ return ((data != other.data)  || (status != other.status))   ;};
                    bool operator ==(iterator& other){  return ((data == other.data)  && (status == other.status))   ;};

                    bool operator !=(iterator* other){  return ((data != other->data) || (status != other->status)) ;};
                    bool operator ==(iterator* other){ return ((data == other->data)  && (status == other->status)) ;};

                    iterator & operator ++(){
                      iterator next_node = appnext();
                      *this = next_node;
                      return *this;};

                    iterator & operator ++(int){
                      iterator next_node = appnext();
                      *this = next_node;
                      return *this;};

                    iterator * add_pos(T& new_elem);
                    iterator * add_all_pos(T& new_elem);

                    void ldbond(iterator * other_node){
                      this->left = other_node;
                      other_node->parent = this;
                    };

                    void rdbond(iterator * node){
                      this->right = node;
                      node->parent = this;
                    };

                    iterator *  ldown(){
                      return left;}

                    iterator * rdown(){
                      return right;}

                    iterator * get_down(){
                      iterator * res = this;
                      while(res->left != nullptr){
                        res = res->ldown();}
                      return  res;}

                    iterator * get_last(){
                      iterator * last = this;
                      while(last->right != nullptr){
                        last = last->rdown();
                      };
                      return last;
                    }

                    iterator * up(){                         
                      if (parent != nullptr){
                              return parent;}
                      else {  std::cout << "вверх нельзя это рут скоре всего\n";
                              return this;}};
                    bool check_right();
                    bool status_check();
                    iterator & next();
                    iterator & appnext();

                    bool onechild(){return (left == nullptr && right != nullptr) || (left != nullptr && right == nullptr);};
                    bool twochild() {return (left!=nullptr && right != nullptr);} ;
                    bool free() {return (left==nullptr && right == nullptr);};

                    void destroy_list();
                    iterator * destroy_branch();  // возвращает ноду под удаленной
                    iterator * root_one();
                    iterator * destroy_hub();
                    void take_pntrs(iterator * other_node);
}; 

iterator * root;          

};

template <class T, class V>
class btreemap {  
            public:
                  btreemap(){root = new btreemap <T,V> ::iterator();};
                 ~btreemap(){delete root;};   
         
            class iterator{
                  public:
                      iterator * parent;
                      iterator * left;
                      iterator * right;
                      bool status;
                      T key;
                      V value;

iterator(const T & ins_key,const V & ins_value):parent(nullptr),left{nullptr},right {nullptr},status(false),key(ins_key),value(ins_value){};
iterator():parent(nullptr), left {nullptr}, right {nullptr}, status(false){};
~iterator(){};
                    iterator  operator = (iterator iter){ 
                      parent = iter.parent;
                      key = iter.key;
                      value = iter.value;
                      left = iter.left;
                      right = iter.right;
                      status = iter.status;
                           return *this;}

                    iterator *  operator = (iterator* iter){ 
                      key = iter->key;
                      value = iter->value;
                      left = iter->left;
                      right = iter->right;
                      parent = iter->parent;
                      status = iter->status;
                           return this;}

                    T & operator *(){ return key;};
                    bool operator !=(iterator&other){ return ((key != other.key)  || (status != other.status))   ;};
                    bool operator ==(iterator& other){  return ((key == other.key)  && (status == other.status))   ;};
                    bool operator !=(iterator* other){  return ((key != other->key)  || (status != other->status)) ;};
                    bool operator ==(iterator* other){ return ((key == other->key)  && (status == other->status))   ;};

                     iterator & operator ++(){
                      iterator next_node = appnext();
                      *this = next_node;
                      return *this;};

                    iterator & operator ++(int){
                      iterator next_node = appnext();
                      *this = next_node;
                      return *this;};

                    iterator * add_pos(T& new_key);

                    void ldbond(iterator * other_node){
                      this->left = other_node;
                      other_node->parent = this;
                    };

                    void rdbond(iterator * node){
                      this->right = node;
                      node->parent = this;
                    };

                    iterator *  ldown(){
                      return left;
                    }

                    iterator * rdown(){
                      return right;
                    }

                    iterator * get_down(){
                      iterator * res = this;
                      while(res->left != nullptr){
                        res = res->ldown();
                        }
                      return  res;
                    }

                    iterator * get_last(){
                      iterator * last = this;
                      while(last->right != nullptr){
                        last = last->rdown();
                      };
                      return last;
                    }

                    iterator * up(){                         
                      if (parent != nullptr){
                              return parent;}
                      else {  std::cout << "вверх нельзя это рут скоре всего\n";
                              return this;}};

                    bool check_right();
                    bool status_check();
                    iterator & next();
                    iterator & appnext();

                    bool  onechild(){return (left == nullptr && right != nullptr) || (left != nullptr && right == nullptr);};
                    bool  twochild() {return (left!=nullptr && right != nullptr);} ;
                    bool  free() {return (left==nullptr && right == nullptr);};

                    void destroy_list();
                    iterator *  destroy_branch();  // возвращает ноду под удаленной
                    iterator *  destroy_hub();
                    void take_pntrs(iterator * other_node);
};

iterator * root;
void delete_root();
void add(const T & key , const V & value);  
};
