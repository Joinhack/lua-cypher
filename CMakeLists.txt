cmake_minimum_required(VERSION 3.15)
project(crypher LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(lua REQUIRED)

file(GLOB SRC "*.c")

if(Lua_FOUND AND NOT TARGET Lua::Lua)
  add_library(Lua::Lua INTERFACE IMPORTED)
  set_target_properties(
    Lua::Lua
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
      INTERFACE_LINK_LIBRARIES "${LUA_LIBRARIES}"
  )
endif()

add_library(crypher SHARED ${SRC})
set_target_properties(crypher PROPERTIES 
  OUTPUT_NAME "crypher"
  PREFIX ""
  SUFFIX ".so"
)
target_link_libraries(crypher PRIVATE Lua::Lua)

enable_testing(true)
add_test(NAME cypher_test COMMAND lua ${CMAKE_CURRENT_SOURCE_DIR}/test.lua)
