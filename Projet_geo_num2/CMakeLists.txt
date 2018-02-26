#- CMAKE version -------------------------------------------------------------#
cmake_minimum_required( VERSION 3.0 FATAL_ERROR)

###############################################################################
# Project                                                                     #
###############################################################################

#- Create project ------------------------------------------------------------#
project( projet_geo_num )
#- Adding compile options ----------------------------------------------------#
add_compile_options( -std=c++11 -Wall )

###############################################################################
# PCL (Point CLoud Library)                                                   #
###############################################################################

#- Package Management --------------------------------------------------------#
find_package( PCL 1.7.1 REQUIRED )

#- Include directories -------------------------------------------------------#
include_directories ( ${PCL_INCLUDE_DIRS} )
link_directories    ( ${PCL_LIBRARY_DIRS} )
add_definitions     ( ${PCL_DEFINITIONS}  )

list( REMOVE_ITEM PCL_LIBRARIES "vtkproj4" )

###############################################################################
# Executable                                                                  #
###############################################################################

#- Source files --------------------------------------------------------------#
file( GLOB sourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
file( GLOB includeFiles "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h" )
file( GLOB inlineFiles "${CMAKE_CURRENT_SOURCE_DIR}/header/*.hpp" )

source_group( "Source" FILES ${sourceFiles} )
source_group( "Include" FILES ${includeFiles} )
source_group( "Inline" FILES ${inlineFiles} )

set( headerFiles ${headerFiles} ${includeFiles} )
set( headerFiles ${headerFiles} ${inlineFiles} )

#- Target --------------------------------------------------------------------#
add_executable( ${PROJECT_NAME} ${sourceFiles} ${headerFiles} )

###############################################################################
# Linked libraries                                                            #
###############################################################################

#- PCL -----------------------------------------------------------------------#
target_link_libraries( ${PROJECT_NAME} ${PCL_LIBRARIES} )

