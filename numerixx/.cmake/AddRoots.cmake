if (NOT NUMERIXX_ROOTS_ADDED)
    message(STATUS "[Numerixx]: Including numerixx::roots library")
    add_library(nxx_roots INTERFACE)
    target_include_directories(nxx_roots INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../roots>)
    add_library(numerixx::roots ALIAS nxx_roots)
    set(NUMERIXX_ROOTS_ADDED TRUE)
endif ()