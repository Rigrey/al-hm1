#include <random>

#include "../include/BSTree.cpp"

int main() {
  BSTree first;
  std::random_device rd;
  std::mt19937_64 g(rd());
  std::uniform_real_distribution<> dis(-1000.0, 1000.0);

  for (int i = 0; i < 300; ++i) {
    int a = dis(g);
    first.add_element(a);
  }
  first.print(Order::preorder);
  std::cout << std::endl << std::endl;
  first.print(Order::inorder);
  std::cout << std::endl << std::endl;
  first.print(Order::postorder);
  std::cout << std::endl << std::endl;

  first.save_to_file("save");

  BSTree second;
  second.load_from_file("save");

  second.print(Order::postorder);
  if (first == second) {
    std::cout << "Second tree eq first tree" << std::endl;
  } else {
    std::cout << "They are not eq" << std::endl;
  }

  return 0;
}
