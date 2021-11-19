#include <iostream>

#include "DataLoader.hpp"
#include "Node.hpp"

int main() {
  auto file_system = DataLoader("example_data/example_1.csv").BuildTree();
  auto textbooks_dir = file_system.GetNode("/Users/devak/Documents/Textbooks");

  for (const auto& child : textbooks_dir.children) {
    std::cout << (child.node_type == NodeType::File ? "File: " : "Dir: ")
              << child.Name()
              << " size of "
              << child.size << std::endl;
  }

  return 0;
}
