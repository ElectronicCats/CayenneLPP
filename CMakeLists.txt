cmake_minimum_required(VERSION 3.13)

if(ESP_PLATFORM)
  # Build CayenneLPP as an ESP-IDF component
  # required because ESP-IDF runs cmake in script mode
  # and needs idf_component_register()
  file(GLOB_RECURSE CAYENNELPP_ESP_SOURCES
    "src/*.*"
  )

  idf_component_register(
    SRCS ${CAYENNELPP_ESP_SOURCES} 
    INCLUDE_DIRS src 
    REQUIRES bblanchon__arduinojson
  )

  return()
endif()
