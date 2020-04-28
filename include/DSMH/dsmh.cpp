#include <iostream>
#include <cstring>
#include "dsmh.h"

/************** MONHOC ***************/
MonHoc::MonHoc(char * mamh, char * tenmh, int stclt, int stcth) {
  strcpy(MAMH, mamh);
  strcpy(TENMH, tenmh);
  STCLT = stclt;
  STCTH = stcth;
}

bool MonHoc::operator > (MonHoc x) {
  return (strcmp(MAMH, x.MAMH) > 0);
}

bool MonHoc::operator < (MonHoc x) {
  return (strcmp(MAMH, x.MAMH) < 0);
}

bool MonHoc::operator == (MonHoc x) {
  return (strcmp(MAMH, x.MAMH) == 0);
}
/************* AVL NODE *****************/
Node::Node(MonHoc k) {
  key = k;
  height = 1;
  left = NULL;
  left = NULL;
}
/************* AVL TREE *****************/

DanhSachMonHoc::DanhSachMonHoc() {
  length = 0;
  root = NULL;
}

//** Utils
int DanhSachMonHoc::height(Node * n) {
  if (n == NULL) {
    return 0;
  }
  return n->height;
}

//** Private methods

Node * DanhSachMonHoc::left_rotate(Node * n) {
  // Exchange nodes
  Node * new_n= n->right;
  n->right = new_n->left;
  new_n->left = n;
  
  // Update height
  n->height = 1 + std::max(height(n->left), height(n->right));
  new_n->height = 1 + std::max(height(new_n->left), height(new_n->right));
  return new_n;
}

Node * DanhSachMonHoc::right_rotate(Node * n) {
  // Exchange nodes
  Node * new_n = n->left;
  n->left = new_n->right;
  new_n->right = n;
  // Update height
  n->height = 1 + std::max(height(n->left), height(n->right));
  new_n->height = 1 + std::max(height(new_n->left), height(new_n->right));
  
  return new_n;
}

Node * DanhSachMonHoc::insert_node(Node * n, MonHoc x) {
  if (n == NULL) {
    length += 1;
    Node * tmp = new Node(x);
    return tmp;
  } 

  if (x > n->key) {
    n->right = insert_node(n->right, x);   
  } else if (x < n->key) {
    n->left = insert_node(n->left, x);
  } 
  n->height = 1 + std::max(height(n->left), height(n->right));
  
  int bal = height(n->left) - height(n->right);

  if (bal > 1) {
    if (x < n->left->key) {
      return right_rotate(n);
    } else {
      n->left = left_rotate(n->left);
      return right_rotate(n);
    } 
  } else if (bal < -1) {
    if (x > n->right->key) {
      return left_rotate(n); 
    } else {
      n->right = right_rotate(n->right);
      return left_rotate(n);
    }
  }
  return n; 
}

Node * DanhSachMonHoc::remove_node(Node * n, MonHoc x) {
  if (n == NULL) 
    return NULL;
  if (x < n->key) {
    n->left = remove_node(n->left, x);
  } else if (x > n->key) {
    n->right = remove_node(n->right, x);
  } else {
    Node * r = n->right;
    if (n->right == NULL) {
      Node * l = n->left;
      delete(n);
      n = l;

    } else if (n->left == NULL) {
      delete(n);
      n = r;
    } else {
      while (r->left != NULL) 
        r = r->left;
      
      n->key = r->key;
      n->right = remove_node(n->right, r->key);
    }
  }

  if (n == NULL) 
    return NULL;
  
  n->height = 1 + std::max(height(n->left), height(n->right));
  int bal = height(n->left) - height(n->right);
  
  if (bal > 1) {
    if (x < n->left->key) {
      return right_rotate(n);
    } else {
      n->left = left_rotate(n->left);
      return right_rotate(n);
    } 
  } else if (bal < -1) {
    if (x > n->right->key) {
      return left_rotate(n); 
    } else {
      n->right = right_rotate(n->right);
      return left_rotate(n);
    }
  }

  return n;
}

Node * DanhSachMonHoc::search_node(Node * n, char * s) {
  if (n == NULL) 
    return NULL;
  
  if (strcmp(s, n->key.TENMH) > 0) 
    return search_node(n->right, s);
  else if (strcmp(s, n->key.TENMH) < 0) 
    return search_node(n->left, s);
  else 
    return n;
}

void DanhSachMonHoc::in_order(Node * node) {
  if (node->left != NULL || node->right != NULL) {
    in_order(node->left);
    std::cout << node->key.TENMH << std::endl;
    in_order(node->right);
  } else {
    std::cout << node->key.TENMH << std::endl;
  }
}

// Public methods
void DanhSachMonHoc::insert(MonHoc x) {
  root = insert_node(root, x);
}

void DanhSachMonHoc::remove(MonHoc x) {
  root = remove_node(root, x);    
}

Node * DanhSachMonHoc::search(char * s) {
  return search_node(root, s);
}

void DanhSachMonHoc::enumerate() {
  in_order(root);
}

