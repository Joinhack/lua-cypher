cmake_minimum_required(VERSION 3.15)
project(cypher)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(Lua REQUIRED)

file(GLOB SRC "*.cpp")

if(Lua_FOUND AND NOT TARGET Lua::Lua)
  add_library(Lua::Lua INTERFACE IMPORTED)
  set_target_properties(
    Lua::Lua
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
      INTERFACE_LINK_LIBRARIES "${LUA_LIBRARIES}"
  )
endif()

add_library(cypher SHARED ${SRC})

if(NOT WIN32 AND UNIX)
  set_target_properties(cypher PROPERTIES 
    OUTPUT_NAME "cypher"
    PREFIX ""
    SUFFIX ".so"
  )
endif()

target_link_libraries(cypher PRIVATE Lua::Lua)

enable_testing(true)
add_test(NAME cypher_test COMMAND  lua ${CMAKE_CURRENT_SOURCE_DIR}/test.lua)
