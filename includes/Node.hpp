#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <filesystem>
#include <memory>

enum NodeType {
  File,
  Directory,
};

struct Node {
  // name of the file or directory
  std::filesystem::path name;
  // The sole size of the file or folder without considering its children
  unsigned long size;
  // The size of subtree from this node
  unsigned long inherit_size;
  // The contents of the folder. Empty vector if node is file
  std::vector<std::unique_ptr<Node>> children;
  // The type of the node (file or directory). Necessary because directory 
  // could be empty, therfore the type of node cannot be inferred from 
  // whether children is empty.
  NodeType node_type;

  Node(const std::filesystem::path& name, unsigned long size, NodeType node_type)
    : name{name}, size{size}, node_type{node_type} {};
};

#endif
