include_directories( . ${PROJECT_SOURCE_DIR}/src )

## inicpp target
set( LIBSOURCES ${PROJECT_SOURCE_DIR}/src/ini.c
                ${PROJECT_SOURCE_DIR}/src/INIReader.cpp
)

add_library( inicpp SHARED ${LIBSOURCES} )

set_target_properties( inicpp PROPERTIES
  COMPILE_FLAGS  "-fPIC -Wall -O2"
  VERSION "${MINOR_REV}.${PATCH_REV}"
  SOVERSION "${MAJOR_REV}"
  OUTPUT_NAME inicpp )

target_link_libraries( inicpp )

install( TARGETS inicpp LIBRARY DESTINATION usr/lib )

## inic target
set( LIBSOURCES ${PROJECT_SOURCE_DIR}/src/ini.c )

add_library( inic SHARED ${LIBSOURCES} )

set_target_properties( inic PROPERTIES
  COMPILE_FLAGS  "-fPIC -Wall -O2"
  VERSION "${MINOR_REV}.${PATCH_REV}"
  SOVERSION "${MAJOR_REV}"
  OUTPUT_NAME inic )

target_link_libraries( inic )

install( TARGETS inic LIBRARY DESTINATION usr/lib )
