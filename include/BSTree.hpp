#ifndef BSTREE_HPP_
#define BSTREE_HPP_

#include <iostream>
#include <fstream>
#include <list>

class Node{
public: 
  int data;
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
  Node* _left;
  Node* _right;
  Node* _prev;
};

#endif // BSTREE_HPP_