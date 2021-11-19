#include <iostream>
#include <sstream>
#include <fstream>

#include "DataLoader.hpp"

std::string StrReplace(std::string str, const std::string& from, 
                       const std::string& to) {
  size_t idx = 0;
  while ((idx = str.find(from, idx)) != std::string::npos) {
    str.replace(idx, from.length(), to);
    idx += to.length();
  }

  return str;
}

FileSystem DataLoader::BuildTree() {
  auto entries = LoadEntries();
  if (entries.empty()) {
    throw std::runtime_error("Empty entries");
  }

  // construct tree
  Node* root_ = new Node("/", 0, NodeType::Directory);

  for (const auto& entry : entries) {
    auto path = entry.path;

    auto curr = root_;
    for (auto dir = ++path.begin(); dir != path.end(); ++dir) {
      Node* next = nullptr;
      for (const auto& child : curr->children) {
        if (child->name == *dir) {
          next = child;
          break;
        }
      }
      if (!next) {
        auto size = dir == --path.end() ? entry.size : 0;
        auto node_type = 
          dir == --path.end() ? NodeType::File : NodeType::Directory;
        next = new Node(*dir, size, node_type);
        curr->children.push_back(next);
      }

      curr = next;
    }
  }

  // calculate inherit_size and sort children by it
  InheritSizeOf(root_);
  SortChildren(root_);

  return FileSystem(root_);
}

std::vector<FileEntry> DataLoader::LoadEntries() {
  std::ifstream file(path_);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }

  std::vector<FileEntry> entries;

  std::string buffer;
  while (std::getline(file, buffer)) {
    std::stringstream ss(buffer);

    FileEntry entry;
    std::string buf;

    std::getline(ss, buf, ',');
    entry.size = std::stol(buf);

    std::getline(ss, buf);
    entry.path = buf;

    entries.push_back(entry);
  }
  
  return entries;
}

unsigned long DataLoader::InheritSizeOf(Node* node) {
  auto size = node->size;
  for (const auto& child : node->children) {
    size += InheritSizeOf(child);
  }
  node->inherit_size = size;
  return size;
}

void DataLoader::SortChildren(Node* node) {
  std::sort(node->children.begin(), node->children.end(), 
            [](Node* a, Node* b) { return a->inherit_size > b->inherit_size; });
  for (const auto& child : node->children) {
    SortChildren(child);
  }
}

