#include "FileSystem.hpp"

FileSystem::FileSystem(DataLoaderBase* const loader) {
  if (loader) {
    root_ = loader->BuildTree();
  } else {
    root_ = std::make_unique<Node>("/", 0, NodeType::Directory);
  }
}

Node* FileSystem::GetNode(const std::filesystem::path& path) const {
  auto curr = root_.get();
  for (auto it = ++path.begin(); it != path.end(); ++it) {
    Node* next = nullptr;
    for (const auto& child : curr->children) {
      if (child->name == *it) {
        next = child.get();
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

FileSystem& FileSystem::getInstanceImpl(DataLoaderBase* const loader) {
  static FileSystem instance{ loader };
  return instance;
}
