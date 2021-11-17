cmake_minimum_required(VERSION 3.12)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(clpp_test
  LppMessageTest.cpp
  LppPolylineTest.cpp
  ../../src/CayenneLPP.cpp
  ../../src/CayenneLPPPolyline.cpp
)

target_include_directories(clpp_test
PRIVATE
  ../../src
)

target_link_libraries(clpp_test
PRIVATE
  Catch2::Catch2WithMain
)
