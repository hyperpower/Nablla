cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Nablla)
if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)
project(${PROJECT_NAME} VERSION 0.1)

set(cmake_cxx_standard 11)
# third-party folder
####################
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(./third-party/googletest)

enable_testing()

# test folder
add_subdirectory(./test/)
