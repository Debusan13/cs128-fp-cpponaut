#include <iostream>

#include <termox/termox.hpp>

using namespace ox;

#include "ui/app.hpp"
#include "DataLoader.hpp"
#include "Node.hpp"

int main() {
  auto loader = DataLoader("example_data/example_1.csv");
  FileSystem::Init(loader);
  auto textbooks_dir = FileSystem::GetInstance().GetNode("/Users/devak/Documents");

  for (const auto& child : textbooks_dir->children) {
    std::cout << (child->node_type == NodeType::File ? "File: " : "Dir: ")
              << child->name << " size of " << child->inherit_size << std::endl;
  }

  return ox::System{}.run<App>();
}
