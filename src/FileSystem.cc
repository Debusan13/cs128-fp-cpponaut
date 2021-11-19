#include "FileSystem.hpp"

FileSystem::FileSystem(Node* root) : root_{root} {};

FileSystem::~FileSystem() {
  // TODO: free memory
}

Node* FileSystem::GetNode(const std::filesystem::path& path) const {
  path.filename(); // to temporary silence warnings
  // TODO
  return root_;
}
