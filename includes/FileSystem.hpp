#ifndef FILE_SYSTEM_HPP_
#define FILE_SYSTEM_HPP_

#include <filesystem>

#include <stdexcept>
#include <memory>

#include "DataLoader.hpp"
#include "Node.hpp"

/* Singleton class that stores the filesystem object */
class FileSystem {
private:
  FileSystem(DataLoader* const loader = nullptr);

  static FileSystem& getInstanceImpl(DataLoader* const loader = nullptr) {
    static FileSystem instance{ loader };
    return instance;
  }

public:
  /*
   * Singleton GetInstance mehtod
   */
  static FileSystem& GetInstance() {
    return getInstanceImpl();
  }

  static FileSystem& Init(DataLoader& loader) {
    return getInstanceImpl(&loader);
  }

  FileSystem(const FileSystem& rhs) = delete;
  FileSystem operator=(const FileSystem& rhs) = delete;

  /*
   * Return the node with given path
   */
  Node* GetNode(const std::filesystem::path& path) const;

private:
  std::unique_ptr<Node> root_;
};

#endif
