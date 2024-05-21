#include "BSTree.hpp"

void BSTree::print_inorder(Node* node) {
  if (node == nullptr) return;
  print_inorder(node->left);
  std::cout << node->data << " ";
  print_inorder(node->right);
}

void BSTree::print_preorder(Node* node) {
  if (node == nullptr) return;
  std::cout << node->data << " ";
  print_preorder(node->left);
  print_preorder(node->right);
}

void BSTree::print_postorder(Node* node) {
  if (node == nullptr) return;
  print_postorder(node->left);
  print_postorder(node->right);
  std::cout << node->data << " ";
}

void BSTree::clear(Node* node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

void BSTree::save_to_file_helper(std::ofstream& file, Node* node) {
    if (node != nullptr) {
        file << node->data << " ";
        save_to_file_helper(file, node->left);
        save_to_file_helper(file, node->right);
    } else {
        file << "# "; // Using "#" to represent null nodes
    }
}


Node* BSTree::get_successor(Node* node) {
  Node* current = node->right;
  while (current != nullptr && current->left != nullptr) {
    current = current->left;
  }
  return current;
}

Node* BSTree::load_from_file_helper(std::ifstream& file) {
    std::string data;
    file >> data;
    if (data == "#") {
        return nullptr; // Null node
    }
    int value = std::stoi(data);
    Node* newNode = new Node(value);
    newNode->left = load_from_file_helper(file);
    newNode->right = load_from_file_helper(file);
    return newNode;
}


bool BSTree::compare_trees(const Node* node1, const Node* node2) const {
    if (node1 == nullptr && node2 == nullptr) {
        return true;
    }
    if (node1 != nullptr && node2 != nullptr) {
        return (node1->data == node2->data) &&
               compare_trees(node1->left, node2->left) &&
               compare_trees(node1->right, node2->right);
    }
    return false;
}

bool BSTree::add_element(int value) {
  Node* newNode = new Node(value);
  if (root == nullptr) {
    root = newNode;
    return true;
  } else {
    Node* current = root;
    Node* parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (value < current->data) {
        current = current->left;
      } else if (value > current->data) {
        current = current->right;
      } else {
        delete newNode;
        return false;  // Элемент уже существует
      }
    }
    if (value < parent->data) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
    return true;
  }
}

bool BSTree::delete_element(int value) {
  Node* parent = nullptr;
  Node* current = root;
  while (current != nullptr && current->data != value) {
    parent = current;
    if (value < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  if (current == nullptr) {
    return false;  // Элемент не найден
  }
  // Удаление узла без потомков или с одним потомком
  if (current->left == nullptr || current->right == nullptr) {
    Node* temp = nullptr;
    if (current->left == nullptr) {
      temp = current->right;
    } else {
      temp = current->left;
    }
    if (parent == nullptr) {
      root = temp;
    } else if (current == parent->left) {
      parent->left = temp;
    } else {
      parent->right = temp;
    }
    delete current;
  }
  // Удаление узла с двумя потомками
  else {
    Node* successor = get_successor(current);
    int temp = successor->data;
    delete_element(successor->data);
    current->data = temp;
  }
  return true;
}

bool BSTree::find_element(int value) {
  Node* current = root;
  while (current != nullptr) {
    if (value == current->data) {
      return true;  // Элемент найден
    } else if (value < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return false;  // Элемент не найден
}

void BSTree::print(Order order) {
  switch (order) {
    case Order::preorder:
      print_preorder(root);
      std::cout << std::endl;

      break;
    case Order::inorder:
      print_inorder(root);
      std::cout << std::endl;

      break;
    case Order::postorder:
      print_postorder(root);
      std::cout << std::endl;

      break;
  }
}

bool BSTree::save_to_file(const std::string& path) {
  std::ofstream file(path);
  if (!file.is_open()) {
    return false;  // Не удалось открыть файл
  }
  save_to_file_helper(file, root);
  file.close();
  return true;
}

bool BSTree::load_from_file(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    return false;  // Не удалось открыть файл
  }
  clear(root);  // Очищаем текущее дерево перед загрузкой нового
  root = load_from_file_helper(file);
  file.close();
  return true;
}

bool BSTree::operator==(const BSTree& rhv) const {
    return compare_trees(root, rhv.root);
}

BSTree::~BSTree() { clear(root); }
