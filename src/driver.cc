#include <iostream>

#include <termox/termox.hpp>

using namespace ox;

#include "DataLoader.hpp"
#include "Node.hpp"

int main() {
  auto file_system = DataLoader("example_data/example_1.csv").BuildTree();
  auto textbooks_dir = file_system.GetNode("/Users/devak/Documents");

  for (const auto& child : textbooks_dir->children) {
    std::cout << (child->node_type == NodeType::File ? "File: " : "Dir: ")
              << child->name << " size of " << child->inherit_size << std::endl;
  }

  return ox::System{}.run<ox::Textbox>("Hello, World!");
}
