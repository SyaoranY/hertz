cmake_minimum_required(VERSION 3.14)

project(Hertz VERSION 1.0.0 LANGUAGES CXX)

option(HERTZ_BUILD_TESTS "Build all of hertz's own tests" OFF)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(Hertz INTERFACE)
add_library(Hertz::Hertz ALIAS Hertz)

target_include_directories(
  Hertz
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(Hertz INTERFACE cxx_std_14)

if (HERTZ_BUILD_TESTS)
  enable_testing()
  include(FetchContent)
  # GoogleTest is only a test dependency.
  # Do not install gtest/gmock together.
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

  # Currently uses GoogleTest only, not GoogleMock.
  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

  FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG v1.17.0
      GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(googletest)

  include(GoogleTest)

  add_executable(test_hertz)
  target_sources(test_hertz PRIVATE tests/test_hertz.cpp)
  target_compile_options(test_hertz PRIVATE -Wall -Wextra -Wpedantic -Werror -O2 -g)
  target_link_libraries(test_hertz PRIVATE Hertz GTest::gtest_main)
  gtest_discover_tests(test_hertz)

endif()

# ------------------------------------------------------------
# Install library
# ------------------------------------------------------------

install(
  TARGETS Hertz
  EXPORT HertzTargets
)

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ------------------------------------------------------------
# Export CMake target
# ------------------------------------------------------------

install(
  EXPORT HertzTargets
  FILE HertzTargets.cmake
  NAMESPACE Hertz::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Hertz
)

# ------------------------------------------------------------
# Package config
# ------------------------------------------------------------

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/HertzConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/HertzConfig.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/Hertz
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/HertzConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/HertzConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/HertzConfigVersion.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/Hertz
)