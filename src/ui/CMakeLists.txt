add_library(rolling_shelter_ui
    MainWindow.h
    HudWidget.h
    screens/GameScreen.h
    screens/ExplorationScreen.h
    screens/CombatScreen.h
    screens/InventoryScreen.h
    screens/BaseScreen.h

    MainWindow.cpp
    HudWidget.cpp
    screens/ExplorationScreen.cpp
    screens/CombatScreen.cpp
    screens/InventoryScreen.cpp
    screens/BaseScreen.cpp

    ${CMAKE_SOURCE_DIR}/resources.qrc
)

# permet de dire au projet de chercher les fichier dans ce dossier auss
target_include_directories(rolling_shelter_ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rolling_shelter_ui PUBLIC
    rolling_shelter_core
    Qt6::Widgets
)
