@[if DEVELSPACE]@
# not sure CMAKE_CURRENT_BINARY_DIR always works
list(APPEND @(PROJECT_NAME)_INCLUDE_DIRS @(CMAKE_CURRENT_BINARY_DIR)/local/usr/include)
@[else]@
list(APPEND @(PROJECT_NAME)_INCLUDE_DIRS ${@(PROJECT_NAME)_DIR}/../../../@(CATKIN_PACKAGE_INCLUDE_DESTINATION))
@[end if]@
