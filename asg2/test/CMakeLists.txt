project(test)

add_executable(ListTest ListTest.cpp)
add_executable(TreeTest TreeTest.cpp)

set_target_properties(ListTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set_target_properties(TreeTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
