set(SOURCE_FILES main.cpp)
add_executable(rethinkmud ${SOURCE_FILES})
target_include_directories(rethinkmud
        PRIVATE include)
