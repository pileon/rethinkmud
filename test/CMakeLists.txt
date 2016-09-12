#cmake_policy(PUSH)
cmake_policy(SET CMP0048 NEW)
add_subdirectory(googletest)
#cmake_policy(POP)

include_directories(${gtest_SOURCE_DIR}/include)

add_subdirectory(rethinkmud)
