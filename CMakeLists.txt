cmake_minimum_required(VERSION 3.14)

project(Hertz VERSION 1.0.0 LANGUAGES CXX)

add_library(Hertz INTERFACE)

target_include_directories(Hertz INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_compile_features(Hertz INTERFACE cxx_std_14)

include(CTest)

if (BUILD_TESTING)

  include(FetchContent)
  FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG v1.17.0
      GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(googletest)

  add_executable(test_hertz)
  target_sources(test_hertz PRIVATE tests/test_hertz.cpp)
  target_compile_options(test_hertz PRIVATE -Wall -Wextra -Wpedantic -Werror -O2 -g)
  target_link_libraries(test_hertz PRIVATE Hertz GTest::gtest_main)

  include(GoogleTest)

  gtest_discover_tests(test_hertz)

endif()