#include <iostream>

#include <termox/termox.hpp>

using namespace ox;

#include "ui/app.hpp"
#include "DataLoader.hpp"
#include "Node.hpp"

int main() {
  auto loader = DataLoader("example_data/example_1.csv");
  FileSystem::Init(loader);
  return ox::System{}.run<App>();
}
