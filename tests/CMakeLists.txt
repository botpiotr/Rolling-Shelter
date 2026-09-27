add_executable(rolling_shelter_tests
    # core/test_TechTree.cpp
    core/test_PlayerState.cpp
    core/test_Inventory.cpp
)
set_target_properties(rolling_shelter_tests PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(rolling_shelter_tests PRIVATE
    rolling_shelter_core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(rolling_shelter_tests)
