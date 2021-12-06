#include "DataLoader.hpp"

std::string StrReplace(std::string str,
                       const std::string& from,
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
  auto root_ = std::make_unique<Node>("/", 0, NodeType::Directory);

  for (const auto& entry : entries) {
    auto path = entry.path;

    Node* curr = root_.get();
    for (auto dir = ++path.begin(); dir != path.end(); ++dir) {
      Node* next = nullptr;
      for (const auto& child : curr->children) {
        if (child->name == *dir) {
          next = child.get();
          break;
        }
      }

      if (!next) {
        auto size = dir == --path.end() ? entry.size : 0;
        auto node_type =
            (dir == --path.end()) ? NodeType::File : NodeType::Directory;
        auto new_node = std::make_unique<Node>(*dir, size, node_type);
        curr->children.push_back(std::move(new_node));
      }

      curr = next;
    }
  }

  // calculate inherit_size and sort children by it
  InheritSizeOf(root_.get()); 
  SortChildren(root_.get());

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
    size += InheritSizeOf(child.get());
  }
  node->inherit_size = size;
  return size;
}

void DataLoader::SortChildren(Node* node) {
  std::sort(node->children.begin(), node->children.end(), [](const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b) {
    return a->inherit_size > b->inherit_size;
  });
  for (const auto& child : node->children) {
    SortChildren(child.get());
  }
}
