add_executable(DumPointerTest
  DumPointerTest.cc
)

target_link_libraries(DumPointerTest
  PRIVATE
  ${GTEST_LIBRARIES}
)

enable_testing()
add_test(NAME DumPointerTest COMMAND DumPointerTest)
