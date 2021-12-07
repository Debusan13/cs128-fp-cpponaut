#include <iostream>
#include "FileSystem.hpp"
#include "DataLoader.hpp"

#ifdef CATCH_CONFIG_MAIN
#   define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

TEST_CASE("Singleton", "Singleton maintains same instance") {
  auto loader = DataLoader("example_data/example_1.csv");
  FileSystem::Init(loader);
  REQUIRE( &FileSystem::GetInstance() == &FileSystem::GetInstance() );
}
