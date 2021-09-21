include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# Creating test executable
add_executable(
        tests

        storage_manager_test.cpp

        ../include/example/sel_storage_manager.hpp
        ../src/example/sel_storage_manager.cpp
        ../include/storage_manager.hpp
        ../include/example/constants.hpp
        ../include/example/sel_event_record.hpp
)
target_link_libraries(tests gtest_main)

# Adding tests
add_test(NAME StorageManager COMMAND FileExist)