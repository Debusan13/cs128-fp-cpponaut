#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <filesystem>

enum NodeType {
  File,
  Directory,
};

struct Node {
  // path of the file
  std::filesystem::path path;
  // The sole size of the file or folder without considering its children
  unsigned long size;
  // The size of subtree from this node
  unsigned long inherit_size;
  // The contents of the folder. Empty vector if node is file
  std::vector<Node> children;
  // The type of the node (file or directory). Necessary because directory 
  // could be empty, therfore the type of node cannot be inferred from 
  // whether children is empty.
  NodeType node_type;

  /* 
   * The name of the file or directory
   */
  std::filesystem::path Name() const { return path.filename(); }
};

#endif
