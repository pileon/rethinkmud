set(RETHINKMUD_TEST_SOURCE_FILES dummy.cpp)

add_executable(rethinkmud_test ${RETHINKMUD_TEST_SOURCE_FILES})
target_include_directories(rethinkmud_test PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(rethinkmud_test gtest gtest_main)
if (NOT STDLIBCXX_WITHOUT_LIBCXXABI)
    target_link_libraries(rethinkmud_test c++abi)
endif()

add_test(NAME rethinkmud_test
        COMMAND rethinkmud_test)
