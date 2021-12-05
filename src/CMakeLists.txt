include_directories("${CMAKE_SOURCE_DIR}/includes")

file(GLOB src_files "*.cc")
file(GLOB header_files "../includes/*.hpp")

add_executable(
  blocks
  ${src_files}
  ${header_files}
)

target_compile_features(blocks PRIVATE cxx_std_20)
target_compile_options(blocks PRIVATE -Wall -Wextra -Werror -pedantic)
target_link_libraries(blocks PRIVATE TermOx)

# Install
install(TARGETS blocks RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
