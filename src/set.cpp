#include "set.h"

template<class T>
typename s21::set<T>::Btree * s21::set<T>::Btree :: add_pos(T& new_elem){

Btree * empty_pos;
if (new_elem == data ){
    empty_pos = this;
}
else if (new_elem < data && left != nullptr) {
  empty_pos = ldown();
  empty_pos = empty_pos->add_pos(new_elem);
}
else if (new_elem > data && right != nullptr){
  empty_pos = rdown();
  empty_pos = empty_pos->add_pos(new_elem);
}
else if ((new_elem > data && right == nullptr) || (new_elem < data && left == nullptr)){
  empty_pos = this;
}
return empty_pos;
}


template <class T>
void  s21::set<T>::add (const T& value) {
        T adding_value = value;
        if (ssize == 0){
        root->data = adding_value;
        ssize++;}
else {
        Btree * adding_pos;
        adding_pos = root->add_pos(adding_value);

        if (adding_value == **adding_pos){
            std:: cout << "copy!!1!" << std::endl;
        }
        else if (adding_value < **adding_pos){
        Btree * new_node = new typename set<T>::Btree(adding_value);
        adding_pos->ldbond(new_node);
        ssize++;
        }
        else if (adding_value > **adding_pos){
        Btree * new_node = new typename set<T>::Btree(adding_value);
        adding_pos->rdbond(new_node);
        ssize++;}
    }
}


template<class T>
typename s21::set<T>::Btree * s21::set <T> :: Btree :: next(){
    bool r = check_right();
    bool s = status_check();
  Btree * nextnode;
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

template<class T>
typename s21::set<T>::Btree * s21::set <T> :: Btree ::appnext(){
Btree * potentialnext = next();
if (potentialnext->status == false){
      potentialnext->status = true;}
else if (potentialnext->status == true){
      potentialnext = potentialnext->appnext();}
return potentialnext;
}

template<class T>
  bool  s21::set <T> :: Btree :: check_right(){
    bool assert = false;
    if (right == nullptr || right->status == true){
        assert = true;}
  return assert;
}

template<class T>
bool  s21::set <T> :: Btree :: status_check(){
bool assert  = false;
if (status == true)
      assert = true;
return assert;
}


template<class T>
void s21::set<T> ::Btree :: destroy_list(){
      if (data < (parent->data)){
          Btree * tmp = up();
          tmp->left  = nullptr;}
      else if (data > (parent->data)){
          Btree * tmp = up();
          tmp->right  = nullptr;} 
    delete this;      
}

template<class T>
void s21::set<T> ::Btree :: unbond_list(){
      if (data < (parent->data)){
          Btree * tmp = up();
          tmp->left  = nullptr;}
      else if (data > (parent->data)){
          Btree * tmp = up();
          tmp->right  = nullptr;}     
}

template<class T>
void s21::set<T>::Btree :: unbond_branch(){
Btree * up_node = up();
Btree * down_node;
if (left != nullptr){
    down_node = ldown();}
else if (right!= nullptr ){
    down_node = rdown();}
if (data > up_node->data){
    up_node->rdbond(down_node);}
else if (data <= up_node->data){ 
    up_node->ldbond(down_node);}         
}

template<class T>
typename s21::set<T>::Btree * s21::set<T>::Btree :: destroy_branch(){
Btree * up_node = up();
Btree * down_node;
if (left != nullptr){
    down_node = ldown();}
else if (right!= nullptr ){
    down_node = rdown();}
if (data > up_node->data){
    up_node->rdbond(down_node);}
else if (data <= up_node->data){ 
        up_node->ldbond(down_node);} 
delete this;  
return  down_node;     
}

template<class T >
typename s21::set<T>::Btree *  s21::set<T>::Btree:: destroy_hub () {
      Btree  *  down_node = rdown(); 
      down_node = down_node->get_down();
      if (down_node->free()){
            down_node->unbond_list();
      }
      else {
         down_node->unbond_branch();
      }
return down_node;
}


template <class T>
s21::set<T> :: set(){
    root = new typename set<T>::Btree();
    fuck_root = new typename set<T>::Btree();
    fuck_root->ldbond(root);
    ssize = 0;
}

template <class T>
s21::set<T> :: set(std::initializer_list<T> const & init_elems){
    root = new typename  set<T> :: Btree();
    fuck_root = new typename set<T> :: Btree();
    fuck_root->ldbond(root);
    ssize = 0;
    for (auto it = init_elems.begin(); it != init_elems.end(); ++it){
        T init_elem = *it;
        add(init_elem);}
}

template <class T>
s21::set<T> :: set(const set<T>  & copyng_set){
    root = new typename  set<T> :: Btree();
    fuck_root = new typename set<T> :: Btree();
    fuck_root->ldbond(root);
    ssize = 0;
    for (auto it = *copyng_set.cbegin(); it != *copyng_set.cend(); ++it){
        T copyng_elem = *it;
        add(copyng_elem);
    }
}

template <class T>
s21::set<T> :: set(set<T> && mooving_set){
    *this = std::move(mooving_set);
}

template <class T>
s21::set<T> :: ~set(){
    clear();
    delete fuck_root;
}


template <class T>
s21::set<T> &  s21::set<T> :: operator = (set<T> && mooving_set) {
    ssize = mooving_set.ssize;
    root = mooving_set.root;
    fuck_root = mooving_set.fuck_root;
    mooving_set.root = nullptr;
    mooving_set.ssize = 0;
    mooving_set.fuck_root = nullptr;
    return *this;
}

template <class T>
void s21::set<T>::clear (){
while(!empty()){
  erase(begin());}
}


template <class T>
typename s21::set<T>::para s21::set<T>::insert(const T& value) {
T const insert_value = value;
    para result;
    result.second = !contains(insert_value); 
    add(insert_value);
    result.first = find(value);
    return result;
}


template <class T>
void s21::set<T>::erase (typename set<T>::Btree * pos){
bool free = pos->free();
bool one = pos->onechild();
bool two = pos->twochild();
bool isroot = (pos->parent == fuck_root);

if (two){
        Btree * new_root = pos->destroy_hub();
        pos->data = new_root->data;
        if (new_root->free()){new_root->destroy_list();}
        else {new_root->destroy_branch();}}

else if (one && isroot){ 
    Btree * new_root = pos->destroy_branch();
    root = new_root;}

else if (one && !isroot){ 
     Btree * new_root = pos->destroy_branch();}

else if (free){
    pos->destroy_list();}

ssize--;
}


template <class T>
void s21::set<T>::swap(set<T>& another_set){
std::swap(root ,another_set.root);
std::swap(ssize ,another_set.ssize);
std::swap(fuck_root ,another_set.fuck_root);
}


template <class T>
void s21::set<T>::merge(set<T>& another_set){
    for (auto it = *another_set.begin(); it != *another_set.end() ; ++it){
        T value = *it;
        add(value); 
    }
// another_set.~set();
}

template <class T>
typename s21::set<T>::Btree * s21::set<T>::find(const T& value) const{
typename set<T>::Btree * node;
if ( ssize == 0){
node = nullptr;
std::cout << "empty";}
else {
T searching_value = value;
node = root->add_pos(searching_value);
if(**node != searching_value){ 
    std::cout << " takogo elementa net\n";}
}
return node;
}


template <class T>
bool s21::set<T>::contains(const T& value) const {
bool contains;
auto node = find(value);
if (**node == value){
    contains = true;
}
return contains;
}


template class s21::set<int>;
template class s21::set<char>;
template class s21::set<std::string>;


// template <typename T>
// void set_test_foo(s21::set<T> &a, std::set<T> &a_eth) {
//   auto iter = a.begin();
//   auto iter_eth = a_eth.begin();
//   for (; iter != a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
//     std::cout << *iter << "  " << *iter_eth << std::endl;
//   }
// //   std::cout << a.size() << " sas size " <<  a_eth.size();
// }



// int main (){
//   s21::set<int> a{1, 2, 3};
//   s21::set<int> b{2, 8, 5, 2, 4, 1, 3, 7, 6, 11, 9, 12, 10, 2};
//   // Act
//   a.merge(b);

//   for ( auto iter = *a.begin(); iter != *a.end(); ++iter){
//     std::cout << *iter << "  " << std::endl;}

// auto sas = a.contains(88);

// // std::cout << sas << "  " << std::endl;

// return 0;
// }
