include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Creating test executable
add_executable(
        tests

        ../include/storage_manager.hpp
        ../src/storage_manager.cpp

        storage_manager_test.cpp
        ../include/constants.hpp)
target_link_libraries(tests gtest_main)

# Adding tests
add_test(NAME StorageManager COMMAND FileExist)