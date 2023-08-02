project(test)

add_executable(test_init_copy_move test_init_copy_move.cpp)

add_executable(test_mutable_directed_no_props test_mutable_directed_no_props.cpp)

add_executable(test_mutable_bidirectional_no_props test_mutable_bidirectional_no_props.cpp)

add_executable(test_mutableprop_directed_w_props test_mutableprop_directed_w_props.cpp)

add_executable(test_mutableprop_bidirectional_w_props test_mutableprop_bidirectional_w_props.cpp)

add_executable(test_topo_sort test_topo_sort.cpp)

set_target_properties(test_init_copy_move
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set_target_properties(test_mutable_directed_no_props
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set_target_properties(test_mutable_bidirectional_no_props
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set_target_properties(test_mutableprop_directed_w_props
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set_target_properties(test_mutableprop_bidirectional_w_props
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set_target_properties(test_topo_sort
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
