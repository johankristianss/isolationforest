project(ml)

cmake_minimum_required(VERSION 3.4.1)

# Enable C++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Optimization compiler and linker flags
if (OPTIMIZE STREQUAL "true")
  MESSAGE("-- Enabling compiler optimizations")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -O3")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flto -O3")
endif()

# Google Test
set(GOOGLETEST_ROOT ${PROJECT_SOURCE_DIR}/vendor/googletest/googletest)
add_library(gtest SHARED ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)
include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

# Vendor includes
include_directories(${PROJECT_SOURCE_DIR}/vendor/eigen)

# Source files
set(ML_SOURCES
  ${PROJECT_SOURCE_DIR}/src/error.cc
  ${PROJECT_SOURCE_DIR}/src/ext_isolation_tree.cc
  ${PROJECT_SOURCE_DIR}/src/isolation_forest.cc
  ${PROJECT_SOURCE_DIR}/src/node.cc
  ${PROJECT_SOURCE_DIR}/src/test.cc
)

# Test source files
set(ML_TEST_SOURCES
  ${PROJECT_SOURCE_DIR}/tests/ext_isolation_tree_test.cc
  ${PROJECT_SOURCE_DIR}/tests/isolation_forest_test.cc
  ${PROJECT_SOURCE_DIR}/tests/isolation_tree_test.cc
  ${PROJECT_SOURCE_DIR}/tests/node_test.cc
)

add_library(ml SHARED ${ML_SOURCES})

# Unit tests
find_package(Threads REQUIRED)
add_executable(ml_unittest ${ML_TEST_SOURCES})
target_link_libraries(ml_unittest ml ${CMAKE_THREAD_LIBS_INIT} gtest)

# Main
add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cc)
target_link_libraries(main ml ${CMAKE_THREAD_LIBS_INIT})

# Pything bindings 
if (PYTHON STREQUAL "true")
  set(Python_ADDITIONAL_VERSIONS, 3.5 3.6 3.7)
  find_package(PythonLibs)
  include_directories(${PROJECT_SOURCE_DIR}/vendor/pybind11/include)
  include_directories(${PYTHON_INCLUDE_DIR})
  file(GLOB ML_PYBIND_SOURCES "${PROJECT_SOURCE_DIR}/src/python_bindings.cpp")
  add_library(mlpy SHARED ${ML_TEST_SOURCES} ${ML_SOURCES} ${ML_PYBIND_SOURCES})
  set_target_properties(mlpy PROPERTIES PREFIX "" OUTPUT_NAME "ml_python.so" SUFFIX "")
  target_link_libraries(mlpy gtest ${PYTHON_LIBRARY})
endif()
