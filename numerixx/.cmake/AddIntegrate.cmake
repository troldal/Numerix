if (NOT NUMERIX_INTEGRATE_ADDED)
    message(STATUS "[Numerixx]: Including numerixx::integrate library")
    add_library(nxx_integrate INTERFACE)
    target_include_directories(nxx_integrate INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../integrate>)
    add_library(numerixx::integrate ALIAS nxx_integrate)
    set(NUMERIX_INTEGRATE_ADDED TRUE)
endif ()