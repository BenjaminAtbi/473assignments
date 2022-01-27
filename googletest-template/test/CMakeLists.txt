add_subdirectory(gtest)
enable_testing()

add_executable(runAllTests
  Dummy.cpp
  # You can create new source files for your tests and add them here,
  # or you can add your tests to Dummy.cpp. Either way will work.
)

target_link_libraries(runAllTests
  gmock gtest gtest_main
  simple
)

add_test(NAME AllTests COMMAND runAllTests)

