#ifndef BSTREE_HPP_
#define BSTREE_HPP_

#include <iostream>
#include <fstream>
#include <list>

class Node{
public:
  Node() : _data(0), _left(nullptr), _right(nullptr), _prev(nullptr) {}
  Node(int value) : _data(value), _left(nullptr), _right(nullptr), _prev(nullptr) {}
  int _data;
  Node* _left;
  Node* _right;
  Node* _prev;
};

class BSTree {
public:
  BSTree();
  BSTree(std::list<int> list);
  ~BSTree();
  bool add_element(int value);
  bool delete_element(int value);
  bool find_element(int value);
  void print(std::ostream& out = std::cout);
  bool save_to_file(const std::string& path);
  bool load_from_file(const std::string& path);

private:
  Node* _root;
};

BSTree::BSTree() : _root() {}

BSTree::BSTree(std::list<int> list) : _root() {
  for (auto it = list.begin(); it != list.end(); it++) {
    add_element(*it);
  }
}

bool BSTree::add_element(int value) {
  if (_root != nullptr && find_element(value)) {
    return false;
  }
  if (_root == nullptr) {
    _root = new Node(value);
    return true;
  }
  Node* current = _root;
  while (true) {
    if (value < current->_data) {
      if (current->_left == nullptr) {
        current->_left = new Node(value);
        current->_left->_prev = current;
        return true;
      }
      current = current->_left;
    } else if (value > current->_data) {
      if (current->_right == nullptr) {
        current->_right = new Node(value);
        current->_right->_prev = current;
        return true;
      }
      current = current->_right;
    } else {
      return false;
    }
  }
}

bool BSTree::find_element(int value) {
  while(true) {
    Node* current = _root;
    if (value == current->_data) {
      return true;
    }
    if (value < current->_data) {
      current = current->_left;
    } else if (value > current->_data) {
      current = current->_right;
    }
  }
}

bool BSTree::delete_element(int value) {
  if (_root == nullptr || !find_element(value)) {
    return false;
  }
  while(true) {
    Node* current = _root;
    if (value == current->_data) {
      if (current->_left == nullptr && current->_right == nullptr) {
        delete current;
        current = nullptr;
        return true;
      }
      if (current->_left == nullptr) {
        Node* right = current->_right;
        Node* prev = current->_prev;
        if (current->_data > prev->_data) {
          prev->_right = right;
        }
        else {
          prev->_left = right;
        }
        delete current;
        current = nullptr;
        _root = right;
        return true;
      }
      if (current->_right == nullptr) {
        Node* left = current->_left;
        delete current;
        current = nullptr;
        _root = left;
        return true;
      }
    }
    if (value < current->_data) {
      current = current->_left;
    } else if (value > current->_data) {
      current = current->_right;
    }
  }
}
#endif // BSTREE_HPP_