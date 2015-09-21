###############################################################################
# CMakeLists.txt --
# 
# By convention, this file is reserved for installing headers (dev headers)
#
# NOTE:   If you are using install targets, convention is to use relative
#         paths
#
# install()
###############################################################################

install( FILES ${PROJECT_SOURCE_DIR}/src/ini.h
  DESTINATION usr/include/inic )

install( FILES ${PROJECT_SOURCE_DIR}/src/INIReader.hpp
  DESTINATION usr/include/inicpp )
