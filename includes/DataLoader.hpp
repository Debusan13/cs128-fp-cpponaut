#ifndef DATA_LOADER_HPP_
#define DATA_LOADER_HPP_

#include <vector>
#include <filesystem>
#include <memory>

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "Node.hpp"

struct FileEntry {
  std::filesystem::path path;
  unsigned long size;
};

class DataLoaderBase {
public:
  virtual std::unique_ptr<Node> BuildTree() const = 0;
};

class DataLoader : public DataLoaderBase {
public:
  DataLoader(std::filesystem::path path) : path_{path} {};
  /*
   * Read csv file, build the Node Tree, and use it to construct a FileSystem 
   * instance
   * @throw std::runtime_error if could not find file, could not open file, or 
   * file is empty
   *
   * Spec:
   * - Node.inherit_size should be computed recursively
   * - Node.children should be sorted by the size of the inherit_size
   *
   * Note: call LoadEntries method from here
   */
  std::unique_ptr<Node> BuildTree() const override;

private:
  std::filesystem::path path_;
  
  /*
   * Load all file entries within the CSV file
   */
  std::vector<FileEntry> LoadEntries() const;

  /* 
   * Recursive helper method for calculating folder size
   */
  unsigned long InheritSizeOf(Node* node) const;

  /* 
   * Recursive helper method to sort child nodes by InheritSize in DSC order
   */
  void SortChildren(Node* node) const;
};

#endif
