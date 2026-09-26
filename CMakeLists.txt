cmake_minimum_required(VERSION 3.16)
project(RollingShelter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Qt6 ---
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# --- Dépendance externe : nlohmann::json ---
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# --- Dépendance externe : GoogleTest (pour les tests) ---
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

# --- Bibliothèque de logique de jeu (testable indépendamment, sans Qt) ---
add_library(rolling_shelter_core
    # src/core/PlayerState.cpp
    # src/core/TechTree.cpp
    # src/core/Location.cpp
    # src/core/Period.cpp
    # src/core/CombatResolver.cpp
)
target_include_directories(rolling_shelter_core PUBLIC src)
target_link_libraries(rolling_shelter_core PUBLIC nlohmann_json::nlohmann_json)

# --- Exécutable principal (UI + core) ---
add_executable(rolling_shelter
    src/main.cpp
    # src/ui/MainWindow.cpp
    # src/ui/HudWidget.cpp
    # src/ui/screens/ExplorationScreen.cpp
    # src/ui/screens/CombatScreen.cpp
    # src/ui/screens/InventoryScreen.cpp
    # src/ui/screens/BaseScreen.cpp
)
target_link_libraries(rolling_shelter PRIVATE rolling_shelter_core Qt6::Widgets)

# --- Tests (ne linkent que core, jamais Qt) ---
enable_testing()
add_executable(rolling_shelter_tests
    # tests/core/test_TechTree.cpp
    # tests/core/test_PlayerState.cpp
)
target_link_libraries(rolling_shelter_tests PRIVATE rolling_shelter_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(rolling_shelter_tests)
