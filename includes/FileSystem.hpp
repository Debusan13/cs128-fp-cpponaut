#ifndef FILE_SYSTEM_HPP_
#define FILE_SYSTEM_HPP_

#include <filesystem>

#in#include <stdexcept>
#include <memory>

#include "Node.hpp"

class FileSystem {
public:
  /*
   * Recieve ownership of the tree
   */

  static DataLoader& GetInstance(){
    static DataLoader instance;
    return instance;
  }
  FileSystem(std::unique_ptr<Node>& root);

  FileSystem(const FileSystem& rhs) = delete;
  FileSystem operator=(const FileSystem& rhs) = delete;

 /*
   * FileSystem has owndership of the tree, thefore needs to free the meory
   */
  // ~FileSystem();

 /*
   * Return the node with given path
   */
  Node* GetNode(const std::filesystem::path& path) const;

private:
  DataLoader(){}
  std::unique_ptr<Node> root_;
};
