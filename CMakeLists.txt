# Bibliothèque de logique de jeu (testable indépendamment)
add_library(rolling_shelter_core
    srccorePlayerState.cpp
    srccoreTechTree.cpp
    # ...
)
target_link_libraries(rolling_shelter_core PUBLIC nlohmann_jsonnlohmann_json)

# Exécutable principal (UI + core)
add_executable(rolling_shelter
    srcmain.cpp
    srcuiMainWindow.cpp
    # ...
)
target_link_libraries(rolling_shelter PRIVATE rolling_shelter_core Qt6Widgets)

# Tests (ne linkent que core, pas Qt)
add_executable(rolling_shelter_tests
    testscoretest_TechTree.cpp
    # ...
)
target_link_libraries(rolling_shelter_tests PRIVATE rolling_shelter_core GTestgtest_main)