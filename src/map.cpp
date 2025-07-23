#include "map.h"

template<class T, class V>
typename s21::map<T,V>::btreemap * s21::map<T,V>::btreemap :: add_pos(T& new_key){

btreemap * empty_pos;
if (key == new_key){
  empty_pos = this;
}
else if (new_key < key && left != nullptr) {
  empty_pos = ldown();
  empty_pos = empty_pos->add_pos(new_key);
}
else if (new_key > key && right != nullptr){
  empty_pos = rdown();
  empty_pos = empty_pos->add_pos(new_key);
}
else if (  (new_key > key && right == nullptr) || (new_key < key && left == nullptr)) {
  empty_pos = this;
}
return empty_pos;
}

template <class T, class V>
void  s21::map<T,V>::add(const T& add_key, const V & add_value) {
        T adding_key = add_key;
        V adding_value = add_value;

        if (size() == 0){
        root->key = adding_key;
        root->value = adding_value;
        mapsize++;}

        else {
        iter * adding_pos;
        adding_pos = root->add_pos(adding_key);
        if (adding_key == **adding_pos){
          std::cout << "zamena!!1\n";
          adding_pos->value = adding_value;
        }
        else if (adding_key < **adding_pos){
        iter * new_node = new typename map<T,V>::btreemap(adding_key, adding_value);
        adding_pos->ldbond(new_node);
        mapsize++;
        }
        else if (adding_key > **adding_pos){
        iter * new_node = new typename map<T,V>::btreemap(adding_key ,adding_value);
        adding_pos->rdbond(new_node);
        mapsize++;}
        }
}

template<class T, class V>
typename s21::map<T,V>::btreemap * s21::map <T ,V> :: btreemap :: next(){
    bool r = check_right();
    bool s = status_check();
  btreemap * nextnode;
    if (!status){
      nextnode = this;
    }
    else if (!r && s){
      nextnode = rdown();
      nextnode = nextnode->get_down();}
    else if (r && s){
      nextnode = up();
    }
  return nextnode;
}

template<class T, class V>
typename s21::map<T, V>::btreemap * s21::map <T ,V> :: btreemap ::appnext(){
btreemap * potentialnext = next();
if (potentialnext->status == false){
      potentialnext->status = true;}
else if (potentialnext->status == true){
      potentialnext = potentialnext->appnext();}
return potentialnext;
}

template<class T, class V>
  bool  s21::map <T ,V> :: btreemap :: check_right(){
    bool assert = false;
    if (right == nullptr || right->status == true){
        assert = true;}
  return assert;
}

template<class T, class V>
bool  s21::map <T, V> :: btreemap :: status_check(){
bool assert  = false;
if (status == true)
      assert = true;
return assert;
}

template<class T, class V>
void s21::map<T ,V> ::btreemap :: destroy_list(){
      if (key < (parent->key)){
          btreemap * tmp = up();
          tmp->left  = nullptr;}
      else if (key > (parent->key)){
          btreemap * tmp = up();
          tmp->right  = nullptr;}  
    delete this;      
}

template<class T, class V>
void s21::map<T,V> ::btreemap :: unbond_list(){
      if (key < (parent->key)){
          btreemap * tmp = up();
          tmp->left  = nullptr;}
      else if (key > (parent->key)){
          btreemap * tmp = up();
          tmp->right  = nullptr;}  
}


template<class T, class V>
void s21::map<T ,V>::btreemap :: unbond_branch(){
btreemap * up_node = up();
btreemap * down_node;
if (left != nullptr){
        down_node = ldown();
        if (key > up_node->key){
        up_node->right = down_node;}
        else {up_node->left = down_node;}
}
else if (right!= nullptr ){
          down_node = rdown();
          if (key > up_node->key){
                up_node->right = down_node;}
                else {up_node->left = down_node;}} 
down_node->parent = up_node; 
}

template<class T, class V>
typename s21::map<T,V>::btreemap * s21::map<T,V>::btreemap :: destroy_branch(){
btreemap * up_node = up();
btreemap * down_node;
if (left != nullptr){
        down_node = ldown();
        if (key > up_node->key){
        up_node->right = down_node;}
        else {up_node->left = down_node;}
}
else if (right!= nullptr ){
          down_node = rdown();
          if (key > up_node->key){
                up_node->right = down_node;}
                else {up_node->left = down_node;}} 
down_node->parent = up_node;
delete this;  
return down_node;
}

template<class T, class V>
typename s21::map<T,V>::btreemap *  s21::map<T,V>::btreemap:: destroy_hub(){
      btreemap  *  down_node = rdown(); 
      down_node = down_node->get_down();
      if (down_node->free()){
            down_node->unbond_list();
      }
      else {
         down_node->unbond_branch();
      }
return down_node;
}


template <class T ,class V>
s21::map<T,V> :: map(){
    root = new typename map<T,V> :: btreemap();
    fuck_root = new typename map<T,V> :: btreemap();
    fuck_root->ldbond(root);
    mapsize = 0;
}

template <class T ,class V>
s21::map<T,V> :: map(std::initializer_list<item> const & init_elems){
    root = new typename map<T,V> :: btreemap();
    fuck_root = new typename map<T,V> :: btreemap();
    fuck_root->ldbond(root);
    mapsize = 0;

    for (auto it = init_elems.begin() ; it != init_elems.end(); ++it){
        T init_key = it->first;
        V init_value = it->second;
          add(init_key,init_value); 
    }
}

template <class T, class V>
s21::map<T,V> :: map(const map<T,V>  & copyng_map){
    root = new typename map<T,V> :: btreemap();
    fuck_root = new typename map<T,V> :: btreemap();
    fuck_root->ldbond(root);
    mapsize = 0;
    for (auto it = *copyng_map.cbegin(); it != *copyng_map.cend(); ++it){
            T copyng_key = it.key;
            V copyng_value = it.value;
            add(copyng_key,copyng_value);}
}

template <class T,class V>
s21::map<T,V> :: map(map<T,V> && mooving_map){
     *this = std::move(mooving_map);
}

template <class T, class V>
s21::map<T,V> :: ~map(){
    // clear();
    delete fuck_root;
    root = nullptr;
    fuck_root = nullptr;
}

template <class T ,class V>
s21::map<T,V> & s21::map<T,V>  :: operator = (map<T,V> && mooving_map) {
    mapsize = mooving_map.mapsize;
    root = mooving_map.root;
    fuck_root = mooving_map.fuck_root;
    mooving_map.mapsize = 0;
    mooving_map.fuck_root = nullptr;
    mooving_map.root = nullptr;
    return *this;
}

template<class T ,class V>
V &  s21::map<T,V>::at(const T &key){
T keykey = key;
iter * node = root->add_pos(keykey);
if (**node == key){
  std::cout << "takogo net no vot poslendit\n";
}
return node->value;
}

template<class T ,class V>
V & s21::map<T,V>::operator [] (const T &key){
V & value = at(key);
return value;
}


template <class T ,class V>
void s21::map<T,V>::clear() {
while(!empty()){
  erase(root);}
}

template <class T ,class V>
typename s21::map<T,V>::inserting  s21::map<T,V>::insert(const typename s21::map<T,V>::item & new_item){
typename s21::map<T,V>::inserting result; 
T keykey = new_item.first;
V value = new_item.second;
typename  map<T,V>::btreemap * node = root->add_pos(keykey);

if (**node != keykey){
  result.second = true;
  add(keykey, value);
  result.first = root->add_pos(keykey);
}
else {
  std::cout << "takoy kluch est";
    result.second = false;
    result.first = node;
}
return result;
}


template <class T ,class V>
typename s21::map<T,V>::inserting  s21::map<T,V>::insert(const T& key , const V & value){
typename s21::map<T,V>::inserting result;  
T keykey = key;
V val = value;
typename  map<T,V>::btreemap * node = root->add_pos(keykey);
if (**node != keykey){
  result.second = true;
  add(keykey, val);
  result.first = root->add_pos(keykey);
}
else {
  std::cout << "takoy kluch est";
    result.second = false;
    result.first = node;
}
return result;
}



template <class T ,class V>
typename s21::map<T,V>::inserting  s21::map<T,V>:: insert_or_assign(const T& key,const V & value){
typename s21::map<T,V>::inserting result; 
T keykey = key;
V val = value;
typename  map<T,V>::btreemap * node = root->add_pos(keykey);
if (**node != keykey){
  result.second = true;
}
else {result.second = false;}
  add(keykey, val);
  result.first = root->add_pos(keykey);
return result;
}


template <class T , class V>
void s21::map<T,V>::erase (typename map<T,V>::btreemap * pos){
bool free = pos->free();
bool one = pos->onechild();
bool two = pos->twochild();
bool isroot = (pos->parent == fuck_root);
if (two){
        btreemap * new_root = pos->destroy_hub();
        pos->value = new_root->value;
        if (new_root->free()){new_root->destroy_list();}
        else {new_root->destroy_branch();}}
else if (one && isroot){ 
    btreemap * new_root = pos->destroy_branch();
    root = new_root;}
else if (one && !isroot){ 
     btreemap * new_root = pos->destroy_branch();}
else if (free){
    pos->destroy_list();}
mapsize--;
}


template <class T ,class V>
void s21::map<T,V>::swap(map<T,V> & other_map){ 
std::swap(root , other_map.root);
std::swap(mapsize , other_map.mapsize);
std::swap(fuck_root , other_map.fuck_root);
}

template <class T ,class V>
void s21::map<T,V>:: merge(map<T,V> & other_map){
typename s21::map<T,V>::inserting result; 
for (iter it = *begin(); it!= *end(); ++it){
    add(it.key, it.value);}
}

template <class T ,class V>
bool s21::map<T,V>:: contains(const T & key ) const {
T keykey = key;
bool contains = false;
iter * adding_pos = root->add_pos(keykey);
        if (**adding_pos == keykey){
    contains = true;}
return contains;
}


template class s21::map<int,int>;
template class s21::map<int,char>;
template class s21::map<char,int>;
template class s21::map<int,std::string>;
template class s21::map<std::string,int>;



// template <typename T, typename V>
// void map_test_foo(s21::map<T, V> &a, std::map <T, V> &a_eth) {
//   auto iter = *a.begin();
//   auto iter_eth = a_eth.begin();
//   for (; iter != *a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
//     std::cout << iter.key << "  " <<  iter_eth->first <<  std::endl;
//     std::cout << iter.value << "  " <<  iter_eth->second <<  std::endl;
//   }
//     std::cout << a.size() << "  " <<  a_eth.size();
// }


// int main(){

// s21::map<int,std::string> b;

// b.add(1 , "tratata");
// b.add(2 , "tratata");

//   // s21::map<int, std::string> b{std::pair<int, std::string>(1, "1"),
//   //                              std::pair<int, std::string>(2, "2"),
//   //                              std::pair<int, std::string>(3, "3")};
//   // Act
//   // s21::map<int, std::string> a(std::move(b));
//   // Assert
//   // std::map<int, std::string> b_eth{std::pair<int, std::string>(1, "1"),
//   //                                  std::pair<int, std::string>(2, "2"),
//   //                                  std::pair<int, std::string>(3, "3")};
//   // std::map<int, std::string> a_eth(std::move(b_eth));
//   // map_test_foo(a, a_eth);
//   // map_test_foo(b, b_eth);

// // map.add(3,5);
// // map.add(1,4);
// // map.add(1,8);

// // for ( auto it = *b.begin(); it != *b.end(); ++it)
// //     std::cout << b.begin()->value << "  " << *it << std::endl;

// //  std::cout << map[2] << "  " << "sgsg"<< std::endl;
// return 0;
// }
