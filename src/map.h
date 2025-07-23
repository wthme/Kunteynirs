#include <initializer_list>
#include <vector>
#include <iostream>
#include <string>

namespace s21 {

template <class T, class V>

class map{

  class btreemap{
                  public:
                      btreemap * parent;
                      btreemap * left;
                      btreemap * right;
                      bool status;
                      T key;
                      V value;

btreemap(const T & ins_key,const V & ins_value):parent(nullptr), left {nullptr},right{nullptr},status(false),key(ins_key),value(ins_value){};
btreemap():parent(nullptr), left{nullptr}, right{nullptr}, status(false){};
~btreemap(){};
                    btreemap & operator = (btreemap iter){ 
                      parent = iter.parent;
                      key = iter.key;
                      value = iter.value;
                      left = iter.left;
                      right = iter.right;
                      status = iter.status;
                           return *this;}

                    btreemap * operator = (btreemap * iter){ 
                      parent = iter->parent;
                      key = iter->key;
                      value = iter->value;
                      left = iter->left;
                      right = iter->right;
                      status = iter->status;
                           return this;}

                    T & operator *(){return key;};
                    bool operator !=(btreemap & other){return ((key != other.key)  || (status != other.status));};
                    bool operator ==(btreemap & other){return ((key == other.key)  && (status == other.status));};
                    bool operator !=(btreemap * other){return ((key != other->key) || (status != other->status));};
                    bool operator ==(btreemap * other){return ((key == other->key)  && (status == other->status));};

                    btreemap & operator ++(){
                      btreemap * next_node = appnext();
                      *this = *next_node;
                      return *this;};

                    btreemap & operator ++(int){
                      btreemap * next_node = appnext();
                      *this = next_node;
                      return *this;};

                    btreemap * add_pos(T& new_elem);

                    void ldbond(btreemap * other_node){
                      left = other_node;
                      other_node->parent = this;};

                    void rdbond(btreemap * node){
                      right = node;
                      node->parent = this;};

                    btreemap * ldown(){return left;}

                    btreemap * rdown(){return right;}

                    btreemap * up(){return parent;}

                    btreemap * get_down(){
                          btreemap * res = this;
                          while(res->left != nullptr){
                          res = res->ldown();}
                      return res;}

                    bool check_right();
                    bool status_check();
                    btreemap * next();
                    btreemap * appnext();
                    bool onechild(){return (left == nullptr && right != nullptr) || (left != nullptr && right == nullptr);};
                    bool twochild(){return (left!=nullptr && right != nullptr);};
                    bool free(){return (left==nullptr && right == nullptr);};
                    void destroy_list();
                    btreemap * destroy_branch();  // возвращает ноду под удаленной
                    void unbond_list(); 
                    void unbond_branch();
                    btreemap * destroy_hub();
                    void take_pntrs(btreemap * other_node);
          };

  using iter = typename map <T,V> :: btreemap;
  using item = typename std::pair <const T, V>;
  using inserting = typename std::pair <typename map<T,V>::btreemap, bool>;
  using insert_list = std::vector< std::pair<typename map<T ,V>::btreemap, bool>>;


  public:
              static const size_t Max_size = 1000;
              size_t mapsize;
              btreemap * root;
              btreemap * fuck_root;
  public:
      map();
      map(std::initializer_list<item> const & init_elems); 
      map(const map<T,V> & copyng_map);
      map(map<T,V> && mooving_map);
      ~map();
      map<T,V> & operator = (map<T,V> && mooving_map);
      V & at(const T &key);
      V & operator [] (const T &key);
      void add (const T& add_key, const V &add_value);  

      btreemap * begin(){
            btreemap * begin;
            if (size() == 0){begin = fuck_root;}
            else {begin = root->get_down();
                  begin->status = true;}
            return begin;};

      btreemap * end(){return fuck_root;};
            
      btreemap * cbegin() const {
            btreemap * begin;
            if (mapsize == 0){begin = fuck_root;}
            else {begin = root->get_down(); begin->status = true;}
            return begin;};

      btreemap * cend() const {return fuck_root;};

      bool empty(){return (mapsize == 0);};
      size_t size() const {return mapsize;};
      size_t max_size() const {return Max_size;};
      void clear();
      std::pair <iter,bool> insert(const item & insert_item);
      std::pair <iter,bool> insert(const T & key, const V & value);
      std::pair <iter,bool> insert_or_assign(const T & key, const V & value);

      void delete_root();
      void erase(iter * pos);
      void swap(map<T,V> & swapping_map);
      void merge(map<T,V> & another_map);
      bool contains(const T& key) const;


void unpack (item value , insert_list vector){
      item  insert_item = value;
      inserting vstavka = insert(insert_item);
      vector.push_back(vstavka);
}

template <typename ... Args>
insert_list insert_many(Args&&... args){ 
      insert_list result;
          (unpack(args,result), ... );
      return result;
      };// здесь распаковка};


};
}  // namespace s21