#ifndef FILE_SYSTEM_HPP_
#define FILE_SYSTEM_HPP_

#include <filesystem>

#include <stdexcept>
#include <memory>

#include "Node.hpp"

/* Singleton class that stores the filesystem object */
class FileSystem {
public:
  /*
   * Singleton GetInstance mehtod
   */
  static FileSystem& GetInstance() {
    if (FileSystem::instance_)
      return *FileSystem::instance_;
    throw std::runtime_error("Instance does not exist");
  }

  /*
   * Recieve ownership of the tree
   */
  FileSystem(std::unique_ptr<Node>& root);

  FileSystem(const FileSystem& rhs) = delete;
  FileSystem operator=(const FileSystem& rhs) = delete;

  /*
   * Return the node with given path
   */
  Node* GetNode(const std::filesystem::path& path) const;

private:
  static FileSystem* instance_;
  std::unique_ptr<Node> root_;
};

#endif
