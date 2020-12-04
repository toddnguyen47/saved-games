cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (WIN32)
  # Copy dll and exe files into the same folder
  # Ref: https://stackoverflow.com/a/55886605
  # Ref: https://stackoverflow.com/a/39807774
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/win32")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/win32")
endif()

project(NupsCli 
  VERSION 1.0
  DESCRIPTION "NUPS Command Line Interface (CLI) version")

add_subdirectory(src)
