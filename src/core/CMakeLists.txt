add_library(rolling_shelter_core
    playerstate.h
    # TechTree.h
    # Location.h
    # Period.h
    # CombatResolver.h

    playerstate.cpp
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
