add_library(rolling_shelter_core

    # HEADERS
    Item.h
    Location.h
    InventoryOwner.h

    PlayerState.h
    Inventory.h
    ItemDatabase.h
    Adventure.h
    # TechTree.h
    # Location.h
    # Period.h
    # CombatResolver.h

    # SRC
    PlayerState.cpp
    Inventory.cpp
    ItemDatabase.cpp
    Adventure.cpp
    # TechTree.cpp
    # Location.cpp
    # Period.cpp
    # CombatResolver.cpp
)
set_target_properties(rolling_shelter_core PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(rolling_shelter_core PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(rolling_shelter_core PUBLIC
    nlohmann_json::nlohmann_json
)
