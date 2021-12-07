#include <iostream>
#include "FileSystem.hpp"
#include "DataLoader.hpp"

#ifdef CATCH_CONFIG_MAIN
#   define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

TEST_CASE("Singleton maintains same instance (example_1.csv)", "[Singleton]") {
  auto loader = DataLoader("example_data/example_1.csv");
  FileSystem::Init(loader);
  REQUIRE( &FileSystem::GetInstance() == &FileSystem::GetInstance() );
}

TEST_CASE("Singleton maintains same instance (example_2.csv)", "[Singleton]") {
  auto loader = DataLoader("example_data/example_2.csv");
  FileSystem::Init(loader);
  REQUIRE( &FileSystem::GetInstance() == &FileSystem::GetInstance() );
}

TEST_CASE("Singleton maintains same instance (example_3.csv)", "[Singleton]") {
  auto loader = DataLoader("example_data/example_3.csv");
  FileSystem::Init(loader);
  REQUIRE( &FileSystem::GetInstance() == &FileSystem::GetInstance() );
}

class MockDataLoaderEmptyDir : public DataLoaderBase {
public:
  std::unique_ptr<Node> BuildTree() const override {
    std::unique_ptr<Node> root = std::make_unique<Node>("/", 0, NodeType::Directory);
    return root;
  }
};

TEST_CASE("FileSystem Empty Directory", "[FileSystem]") {
  auto loader = MockDataLoaderEmptyDir();
  FileSystem::Init(loader);
  
  REQUIRE_NOTHROW( FileSystem::GetInstance().GetNode("/") );
  REQUIRE_THROWS( FileSystem::GetInstance().GetNode("/nonexisting_file") );
}

TEST_CASE("FileSystem File Size Correctness", "[FileSystem]") {
  auto loader = DataLoader("example_data/example_1.csv");
  FileSystem::Init(loader);
  
  auto textbooks_dir = FileSystem::GetInstance().GetNode("/Users/devak/Documents");
  auto child_0 = textbooks_dir->children[0].get();
  REQUIRE( child_0->name == "Textbooks" );
  REQUIRE( child_0->inherit_size == 1200000 );
  auto child_1 = textbooks_dir->children[1].get();
  REQUIRE( child_1->name == "leetcode_company_wise_questions" );
  REQUIRE( child_1->inherit_size == 59560 );
  auto child_2 = textbooks_dir->children[2].get();
  REQUIRE( child_2->name == "notes" );
  REQUIRE( child_2->inherit_size == 30528 );
}

