cmake_minimum_required(VERSION 2.8)
project(siemens_drivers)

find_package(catkin REQUIRED)


set(dk16xx_pnio_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/local)

INCLUDE(ExternalProject)
ExternalProject_Add(
  dk16xx_pnio_extproj
  GIT_REPOSITORY
    https://github.com/gavanderhoorn/siemens_drivers.git
  GIT_TAG
    upstream_patched
  PREFIX
    externals
  CONFIGURE_COMMAND
    ""
  BUILD_IN_SOURCE
    TRUE
  INSTALL_DIR
    ${dk16xx_pnio_INSTALL_DIR}
  INSTALL_COMMAND
    make DESTDIR=${dk16xx_pnio_INSTALL_DIR} install
)


add_library(tgt_dk16xx_l2interface SHARED IMPORTED)
set_property(TARGET tgt_dk16xx_l2interface PROPERTY IMPORTED_LOCATION
  ${dk16xx_pnio_INSTALL_DIR}/usr/lib/libdk16xx_l2interface.so)
set_target_properties(tgt_dk16xx_l2interface PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(tgt_dk16xx_l2interface dk16xx_pnio_extproj)

add_library(tgt_dk16xx_pniousr SHARED IMPORTED)
set_property(TARGET tgt_dk16xx_pniousr PROPERTY IMPORTED_LOCATION
  ${dk16xx_pnio_INSTALL_DIR}/usr/lib/libdk16xx_pniousr.so)
set_target_properties(tgt_dk16xx_pniousr PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(tgt_dk16xx_pniousr dk16xx_pnio_extproj)

add_library(tgt_dk16xx_servusr SHARED IMPORTED)
set_property(TARGET tgt_dk16xx_servusr PROPERTY IMPORTED_LOCATION
  ${dk16xx_pnio_INSTALL_DIR}/usr/lib/libdk16xx_servusr.so)
set_target_properties(tgt_dk16xx_servusr PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(tgt_dk16xx_servusr dk16xx_pnio_extproj)


catkin_package(
  CFG_EXTRAS
    ${PROJECT_NAME}-extras.cmake
  EXPORTED_TARGETS
    dk16xx_pnio_extproj
  LIBRARIES
    tgt_dk16xx_l2interface
    tgt_dk16xx_pniousr
    tgt_dk16xx_servusr
)

install(
  # TODO: how to get CMake to strip the runtime path from these?
  FILES
    ${dk16xx_pnio_INSTALL_DIR}/usr/lib/libdk16xx_l2interface.so
    ${dk16xx_pnio_INSTALL_DIR}/usr/lib/libdk16xx_pniousr.so
    ${dk16xx_pnio_INSTALL_DIR}/usr/lib/libdk16xx_servusr.so
  DESTINATION
    ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(
  DIRECTORY
    ${dk16xx_pnio_INSTALL_DIR}/usr/include/dk16xx
  DESTINATION
    ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
