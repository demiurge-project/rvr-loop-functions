# Set up ARGoS compilation information
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})
link_directories(${ARGOS_LIBRARY_DIRS})
link_directories(
	${CMAKE_BINARY_DIR}/src
    )

add_library(big_foraging_loopfunc SHARED BigForagingTwoSpotsLoopFunc.h BigForagingTwoSpotsLoopFunc.cpp)
target_link_libraries(big_foraging_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)

add_library(big_grid_exploration_loopfunc SHARED BigGridExplorationLoopFunc.h BigGridExplorationLoopFunc.cpp ${LOOP_HEADERS} ${LOOP_SOURCES})
target_link_libraries(big_grid_exploration_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)

add_library(chocolate_big_aac_loopfunc SHARED ChocolateBigAACLoopFunc.h ChocolateBigAACLoopFunc.cpp ${LOOP_HEADERS} ${LOOP_SOURCES})
target_link_libraries(chocolate_big_aac_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)

add_library(test_loopfunc SHARED TestLoopFunc.h TestLoopFunc.cpp ${LOOP_HEADERS} ${LOOP_SOURCES})
target_link_libraries(test_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)
