set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

# gtest demo
add_executable(
    hello_test
    demo/hello_test.cpp
)

target_link_libraries(
  hello_test
  PRIVATE
    gtest
    gtest_main
)

# gflags demo
add_executable(
    glfags_test
    demo/gflags_test.cpp
)

target_link_libraries(
  glfags_test
  PRIVATE
    gflags
)

# leveldb demo
add_executable(
    leveldb_test
    demo/leveldb_test.cpp
)

target_link_libraries(
    leveldb_test
    PRIVATE
      leveldb
)

# protobuf
# find_package(Protobuf REQUIRED)

# include_directories(${PROTOBUF_INCLUDE_DIR})
# protobuf_generate_cpp(PROTO_SRC PROTO_HEADER demo/protobuf_test.proto)
# add_library(proto ${PROTO_HEADER} ${PROTO_SRC})

# add_executable(
#     protobuf_test
#     demo/protobuf_test.cpp
# )

# target_link_libraries(
#     protobuf_test
#     PRIVATE
#       include(CheckPrototypeDefinition)
#       ${PROTOBUF_LIBRARY}
# )