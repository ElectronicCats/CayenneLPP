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
  LppPowerMeasurementTest.cpp
  ../../src/SFloat16.cpp
  ../../src/CayenneLPP.cpp
  ../../src/CayenneLPPByteBuffer
  ../../src/CayenneLPPMessage.cpp
  ../../src/CayenneLPPPolyline.cpp
  ../../src/CayenneLPPPowerMeasurement.cpp
)

set_property(TARGET clpp_test
  PROPERTY CXX_STANDARD 17
)

target_compile_options(clpp_test
PRIVATE
  -Wall -Wextra -Wpedantic -Werror
)

target_include_directories(clpp_test
PRIVATE
  ../../src
)

target_link_libraries(clpp_test
PRIVATE
  Catch2::Catch2WithMain
)
