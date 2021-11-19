#ifndef DATA_LOADER_HPP_
#define DATA_LOADER_HPP_

#include <vector>
#include <filesystem>

#include "FileSystem.hpp"

struct FileEntry {
  std::filesystem::path path;
  unsigned long size;
};

class DataLoader {
public:
  DataLoader(std::filesystem::path path) : path_{path} {};
  /*
   * Read csv file, build the Node Tree, and use it to construct a FileSystem instance
   * @throw std::runtime_error if could not find file or open file
   *
   * Spec:
   * - Directory should have a size of 4 kb (4096)
   * - Node.inherit_size should be computed recursively
   * - Node.children should be sorted by the size of the inherit_size
   *
   * Note: call LoadEntries method from here
   */
  FileSystem BuildTree();

private:
  std::filesystem::path path_;
  
  /*
   * Load all file entries within the CSV file
   */
  std::vector<FileEntry> LoadEntries();
};

#endif
