#include "multiset.h"

template <class T>
s21::multiset<T> :: multiset(){
    root = new typename multiset<T>::Btree();
    fuck_root = new typename multiset<T>::Btree();
    fuck_root->ldbond(root);
    multisize = 0;
}

template <class T>
s21::multiset<T> :: multiset(std::initializer_list<T> const & init_elems){
    root = new typename  multiset<T> :: Btree();
    fuck_root = new typename multiset<T> :: Btree();
    fuck_root->ldbond(root);
    multisize = 0;
    for (auto it = init_elems.begin(); it != init_elems.end(); ++it){
        T init_elem = *it;
        add(init_elem);}
}

template <class T>
s21::multiset<T> :: multiset(const multiset<T>  & copyng_set){
    root = new typename  multiset<T> :: Btree();
    fuck_root = new typename multiset<T> :: Btree();
    fuck_root->ldbond(root);
    multisize = 0;

    for (auto it = *copyng_set.cbegin(); it != *copyng_set.cend(); ++it){
            T copyng_elem = *it;
            add(copyng_elem);
    }
}

template <class T>
s21::multiset<T> :: multiset(multiset<T> && mooving_set){
    *this = std::move(mooving_set);
}

template <class T>
s21::multiset<T> &  s21::multiset<T> :: operator = (multiset<T> && mooving_set) {
    multisize = mooving_set.multisize;
    root = mooving_set.root;
    fuck_root = mooving_set.fuck_root;
    mooving_set.multisize = 0;
    mooving_set.fuck_root = nullptr;
    mooving_set.root = nullptr;
    return *this;
}

template <class T>
s21::multiset<T> :: ~multiset() {
    clear();
    delete fuck_root;
    root = nullptr;
    fuck_root = nullptr;
}

template<class T>
void s21::multiset<T> ::Btree :: destroy_list(){
      if (data < (parent->data)){
          Btree * tmp = up();
          tmp->left  = nullptr;}
      else if (data > (parent->data)){
          Btree * tmp = up();
          tmp->right  = nullptr;} 
    delete this;      
}

template<class T>
void s21::multiset<T> ::Btree :: unbond_list(){
      if (data < (parent->data)){
          Btree * tmp = up();
          tmp->left  = nullptr;}
      else if (data > (parent->data)){
          Btree * tmp = up();
          tmp->right  = nullptr;}     
}

template<class T>
void s21::multiset<T>::Btree :: unbond_branch(){
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
typename s21::multiset<T>::Btree * s21::multiset<T>::Btree :: destroy_branch(){
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
typename s21::multiset<T>::Btree *  s21::multiset<T>::Btree:: destroy_hub () {
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
void s21::multiset<T>:: erase(typename s21::multiset<T>::Btree * pos){
typename s21::multiset<T>::Btree * deleting_node = pos;
bool free =pos->free();
bool one = pos->onechild();
bool two = pos->twochild();
bool isroot = (pos->parent == fuck_root);

if (two){
        Btree *  new_root = pos->destroy_hub();
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

multisize--;
}


template<class T>
void s21::multiset<T>::Btree::take_pntrs( s21::multiset<T>::Btree * other_node){
parent = other_node->parent;
left = other_node->left;
right = other_node->right;
}
      
template<class T>
typename s21::multiset<T>::Btree * s21::multiset <T> :: Btree :: next(){
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
typename s21::multiset<T>::Btree * s21::multiset <T> :: Btree ::appnext(){
Btree * potentialnext = next();
if (potentialnext->status == false){
      potentialnext->status = true;}
else if (potentialnext->status == true){
      potentialnext = potentialnext->appnext();}
return potentialnext;
}

template<class T>
  bool  s21::multiset <T> :: Btree :: check_right(){
    bool assert = false;
    if (right == nullptr || right->status == true){
        assert = true;}
  return assert;
}

template<class T>
bool  s21::multiset <T> :: Btree :: status_check(){
bool assert  = false;
if (status == true)
      assert = true;
return assert;
}

template<class T>
typename s21::multiset<T>::Btree * s21::multiset<T>::Btree :: add_all_pos(T& new_elem){

Btree * empty_pos;
if (new_elem <= data && left != nullptr) {
  empty_pos = ldown();
  empty_pos = empty_pos->add_all_pos(new_elem);
}
else if (new_elem > data && right != nullptr){
  empty_pos = rdown();
  empty_pos = empty_pos->add_all_pos(new_elem);
}
else if ((new_elem > data && right == nullptr) || (new_elem <= data && left == nullptr)){
  empty_pos = this;
}
return empty_pos;
}

template <class T>
void  s21::multiset<T>::add (const T& value) {
        T adding_value = value;
        if (multisize == 0){
        root->data = adding_value;
        multisize++;}
else {
        Btree * adding_pos;
        adding_pos = root->add_all_pos(adding_value);

        if (adding_value <= **adding_pos){
        Btree * new_node = new typename multiset<T>::Btree(adding_value);
        adding_pos->ldbond(new_node);
        multisize++;
        }
        else if (adding_value > **adding_pos){
        Btree * new_node = new typename multiset<T>::Btree(adding_value);
        adding_pos->rdbond(new_node);
        multisize++;}
    }
}

template<class T>
void s21::multiset<T>:: clear(){
while(!empty()){
  erase(root);}
}


template <class T>
void s21::multiset<T>::swap(multiset<T>& another_set){
std::swap(root ,another_set.root );
std::swap(multisize ,another_set.multisize );
std::swap(fuck_root ,another_set.fuck_root );
}

template <class T>
void s21::multiset<T>::merge(multiset<T>& another_set){
    for (auto it = *another_set.begin(); it != *another_set.end() ; ++it){
        add(*it); 
    }
}

template <class T>
typename s21::multiset<T>::Btree * s21::multiset<T>::find(const T& value) const {
s21::multiset<T> :: Btree * node;
T searching_value = value;
node = root->add_all_pos(searching_value);
return node;
}

template <class T>
bool s21::multiset<T>::contains(const T& value) const {

bool contains = false;
s21::multiset<T> :: Btree * node = find(value);
if (**node == value){
    contains = true;
}
return contains;
}


template <class T>
typename s21::multiset<T>::Btree * s21::multiset<T>::insert(const T& value) {
T  const insert_value = value;
s21::multiset<T> :: Btree * node;
add(insert_value);
node = find(value);
return node;
}

template <class T>
size_t s21::multiset<T>::count(const T& value) const {
size_t count = 0;
for(auto it = *cbegin(); it != *cend(); ++it){
    if (*it == value){
        count++;}
}
return count;
}


template class s21::multiset<int>;
template class s21::multiset<char>;
template class s21::multiset<std::string>;


template <typename T>
void multiset_test_foo(s21::multiset<T> &a, std::multiset<T> &a_eth) {
  auto iter = *a.begin();
  auto iter_eth = a_eth.begin();
  for (; iter != *a.end() && iter_eth != a_eth.end(); ++iter, ++iter_eth) {
    std::cout << *iter <<"  " <<  *iter_eth;
  }
  iter = a.end();
  iter_eth = a_eth.end();
   std::cout << a.size() << "  "  << a_eth.size();
}




// int main(){

// // s21::multiset<int> s;

// // s.add(25);
// // s.add(17);
// // s.add(17);
// // s.add(68);
// // s.add(34);

// // // std::cout << **s.begin() << std::endl;


// // for (auto it = *s.begin(); it != *s.end(); ++it)
// //     std::cout << *it << std::endl;

// // std::cout << **s.root<< std::endl;

//   s21::multiset<int> a{ 2,  2, 3 ,1 ,1};
//   // Assert

// auto t = a.equal_range(1);

// //   for (auto it = *a.begin(); it != *a.end(); ++it)
// //     std::cout << *it << std::endl;


// return 0;
// }

