if (NOT NUMERIXX_OPTIMIZE_ADDED)
    message(STATUS "[Numerixx]: Including numerixx::optimize library")
    add_library(nxx_optimize INTERFACE)
    target_include_directories(nxx_optimize INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../optimize>)
    add_library(numerixx::optimize ALIAS nxx_optimize)
    set(NUMERIXX_OPTIMIZE_ADDED TRUE)
endif ()