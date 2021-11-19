#include "FileSystem.hpp"

FileSystem::FileSystem(Node* root) : root_{root} {};

FileSystem::~FileSystem() {
  // TODO: free memory
}

Node* FileSystem::GetNode(const std::filesystem::path& path) const {
  auto curr = root_;
  for (auto it = ++path.begin(); it != path.end(); ++it) {
    Node* next = nullptr;
    for (const auto& child : curr->children) {
      if (child->name == *it) {
        next = child;
        break;
      }
      if (!next) {
        throw std::runtime_error("Path not found");
      }
    }
    curr = next;
  }
  return curr;
}
