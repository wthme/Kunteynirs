#include "Btree.h"

template<class T>
typename Btree<T>::iterator * Btree<T>::iterator :: add_pos(T& new_elem){

iterator * empty_pos;
if (data == new_elem){
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
else if (  (new_elem > data && right == nullptr)  ||  (new_elem < data && left == nullptr)  ) {
  empty_pos = this;
}
return empty_pos;
}


template<class T>
typename Btree<T>::iterator * Btree<T>::iterator :: add_all_pos(T& new_elem){

iterator * empty_pos;
if (new_elem <= data && left != nullptr) {
  empty_pos = ldown();
  empty_pos = empty_pos->add_pos(new_elem);
}
else if (new_elem > data && right != nullptr){
  empty_pos = rdown();
  empty_pos = empty_pos->add_pos(new_elem);
}
else if ( (new_elem > data && right == nullptr)  ||  (new_elem <= data && left == nullptr)  ) {
  empty_pos = this;
}
return empty_pos;
}



template<class T , class V>
typename btreemap<T,V>::iterator * btreemap<T,V>::iterator :: add_pos(T& new_key){

iterator * empty_pos;
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
else if (  (new_key > key && right == nullptr)  ||  (new_key < key && left == nullptr)  ) {
  empty_pos = this;
}
return empty_pos;
}


template<class T ,class V>
void  btreemap<T,V>::delete_root(){

btreemap<T,V>::iterator * new_root;

if (root->onechild()) {new_root = root->destroy_branch();
}
else if (root->twochild()) {new_root = root->destroy_hub();

    if (root->right->free()){
          new_root->take_pntrs(root);
          new_root->right = nullptr;}
    else {
          new_root->take_pntrs(root);}
}
else {new_root = nullptr;}

delete root;
root = new_root;

}


// template <class T,class V>
// void  btreemap<T,V>::add (const T& add_key , const V & add_value) {
//         T adding_key = add_key;
//         V adding_value = add_value;

//         if (size() == 0){
//         bmap->root->key = adding_key;
//         bmap->root->value = adding_value;
//         mapsize++;}

//         else {
//         iter * adding_pos;
//         adding_pos = bmap->root->add_pos(adding_key);
//         if (adding_key == **adding_pos){
//           std::cout << "zamena!!1\n";
//           adding_pos->value = adding_value;
//         }
//         else if (adding_key < **adding_pos){
//         iter * new_node = new typename btreemap<T ,V>::iterator(adding_key, adding_value);
//         adding_pos->ldbond(new_node);
//         mapsize++;
//         }
//         else if (adding_key > **adding_pos){
//         iter * new_node = new typename btreemap<T ,V>::iterator(adding_key ,adding_value);
//         adding_pos->rdbond(new_node);
//         mapsize++;}
//         }
// }





template<class T>
bool  Btree <T> :: iterator :: status_check(){
bool assert  = false;
if (status == true)
      assert = true;
return assert;
}

template<class T ,class V>
bool  btreemap <T ,V> :: iterator :: status_check(){
bool assert  = false;
if (status == true)
      assert = true;
return assert;
}


template<class T>
  bool  Btree <T> :: iterator :: check_right(){
    bool assert = false;
    if (right == nullptr || right->status == true){
        assert = true;}
  return assert;
}

template<class T ,class V>
  bool  btreemap <T ,V> :: iterator :: check_right(){
    bool assert = false;
    if (right == nullptr || right->status == true){
        assert = true;}
  return assert;
}


template<class T, class V>
  typename btreemap <T , V>::iterator &  btreemap <T,V> :: iterator :: next(){
    bool r = check_right();
    bool s = status_check();
  iterator * nextnode;
    if (!status){
      nextnode = this;
    }
    else if ( !r && s){
      nextnode = rdown();
      nextnode = nextnode->get_down();}
    else if (r && s){
      nextnode = up();
    }
  return *nextnode;
}


template<class T>
  typename Btree <T>::iterator &  Btree <T> :: iterator :: next(){
    bool r = check_right();
    bool s = status_check();
  iterator * nextnode;
    if (!status){
      nextnode = this;
    }
    else if ( !r && s){
      nextnode = rdown();
      nextnode = nextnode->get_down();}
    else if (r && s){
      nextnode = up();
    }
  return *nextnode;
}

template<class T , class V>
  typename btreemap <T ,V>::iterator &  btreemap <T ,V> :: iterator :: appnext(){
    iterator & potentialnext = next();
if (potentialnext.status == false){
      potentialnext.status = true;}
else if (potentialnext.status == true){
      potentialnext = potentialnext.appnext();
    }
return potentialnext;
}

template<class T>
  typename Btree <T>::iterator &  Btree <T> :: iterator :: appnext(){
    iterator & potentialnext = next();
if (potentialnext.status == false){
      potentialnext.status = true;}
else if (potentialnext.status == true){
      potentialnext = potentialnext.appnext();
    }
return potentialnext;
}

template<class T ,class V>
void btreemap <T ,V> :: iterator :: destroy_list(){
      if (key < (parent->key)){
          iterator * tmp = up();
          tmp->left  = nullptr;}
      else if (key > (parent->key)){
          iterator * tmp = up();
          tmp->right  = nullptr;}  
  // delete this; 
}

template<class T>
void Btree <T> :: iterator :: destroy_list(){
      if (data < (parent->data)){
          iterator * tmp = up();
          tmp->left  = nullptr;}
      else if (data > (parent->data)){
          iterator * tmp = up();
          tmp->right  = nullptr;} 
  delete this;         
}

template<class T , class V>
typename btreemap <T,V> :: iterator *      btreemap <T,V> :: iterator :: destroy_branch(){
iterator * up_node = up();
iterator * down_node;

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

return down_node;
}

template<class T>
typename Btree <T> :: iterator *  Btree <T> :: iterator :: destroy_branch(){
iterator * up_node = up();
iterator * down_node;

if (left != nullptr){
        down_node = ldown();
        if (data > up_node->data){
        up_node->right = down_node;}
        else {up_node->left = down_node;}
}
else if (right!= nullptr ){
          down_node = rdown();
          if (data > up_node->data){
                up_node->right = down_node;}
                else {up_node->left = down_node;}}
  
down_node->parent = up_node;

return down_node;
}

template<class T , class V>
typename btreemap <T ,V> :: iterator *  btreemap <T,V> :: iterator :: destroy_hub () {
      iterator *  down_node = rdown(); 
      down_node = down_node->get_down();
      if (down_node->free()){
            down_node->destroy_list();
      }
      else {
         down_node->destroy_branch();
      }
  return down_node;
}

template<class T>
typename Btree <T> :: iterator *  Btree <T> :: iterator :: destroy_hub () {
      iterator *  down_node = rdown(); 
      down_node = down_node->get_down();
      if (down_node->free()){
            down_node->destroy_list();
      }
      else {
         down_node->destroy_branch();
      }
  return down_node;
}

template<class T ,class V>
void btreemap<T,V>::iterator::take_pntrs(iterator * other_node){
parent = other_node->parent;
left = other_node->left;
right = other_node->right;
}

template<class T>
void Btree<T>::iterator::take_pntrs(iterator * other_node){
parent = other_node->parent;
left = other_node->left;
right = other_node->right;
}
                 
template class Btree<int>;
// template class Btree<std::string>;

template class btreemap<int,int>;
template class btreemap<int,std::string>;
template class btreemap<std::string ,int>;
template class btreemap<int,char>;
template class btreemap<char,int>;
// template class Btree<char>;




// int main(){

//   Btree<int> b;


//   return 0;
// }
