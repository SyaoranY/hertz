cmake_minimum_required(VERSION 3.20)

project(hertz_consumer LANGUAGES CXX)

find_package(Hertz CONFIG REQUIRED)

add_executable(hertz_consumer main.cpp)

target_link_libraries(
  hertz_consumer
  PRIVATE
    Hertz::Hertz
)