add_subdirectory(core)
add_subdirectory(ui)

add_executable(rolling_shelter
    main.cpp
)

target_link_libraries(rolling_shelter PRIVATE
    rolling_shelter_ui
)

