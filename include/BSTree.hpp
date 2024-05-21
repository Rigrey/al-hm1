#include <fstream>
#include <initializer_list>
#include <iostream>
#include <string>

struct Node {
  int data;
  Node* left;
  Node* right;
  Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

enum class Order : int { preorder, inorder, postorder };

class BSTree {
 private:
  Node* root;

  void print_inorder(Node* node);
  void print_preorder(Node* node);
  void print_postorder(Node* node);

  void clear(Node* node);
  void save_to_file_helper(std::ofstream& file, Node* node);
  Node* load_from_file_helper(std::ifstream& file);

  bool compare_trees(const Node* node1, const Node* node2) const;

  Node* get_successor(Node* node);

 public:
  BSTree() : root(nullptr) {}  // конструктор по умолчанию
  BSTree(std::initializer_list<int> list)
      : root(nullptr) {  // конструктор с параметром
    for (int value : list) {
      add_element(value);
    }
  }
  bool add_element(int value);
  bool delete_element(int value);
  bool find_element(int value);
  void print(Order order = Order::preorder);
  bool save_to_file(const std::string& path);
  bool load_from_file(const std::string& path);
  bool operator==(const BSTree& rhv) const;
  ~BSTree();
};
