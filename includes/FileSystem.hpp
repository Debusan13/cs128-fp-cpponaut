#ifndef FILE_SYSTEM_HPP_
#define FILE_SYSTEM_HPP_

#include <filesystem>

#include "Node.hpp"

class FileSystem {
public:
  /*
   * Recieve ownership of the tree
   */
  FileSystem(Node* root);

  FileSystem(const FileSystem& rhs) = delete;
  FileSystem operator=(const FileSystem& rhs) = delete;

  /* 
   * FileSystem has owndership of the tree, thefore needs to free the memory 
   */
  ~FileSystem();

  /* 
   * Return the node with given path
   */
  Node* GetNode(const std::filesystem::path& path) const;

private:
  Node* root_;
};

#endif
