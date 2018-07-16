cmake_minimum_required(VERSION 3.6)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "My multi config types" FORCE)

project(ZegoLiveDemo)


macro(ADD_FRAMEWORK fwname appname)
find_library(FRAMEWORK_${fwname}
    NAMES ${fwname}
    PATHS ${CMAKE_OSX_SYSROOT}/System/Library
    PATH_SUFFIXES Frameworks
    NO_DEFAULT_PATH)
if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
    MESSAGE(ERROR ": Framework ${fwname} not found")
else()
    TARGET_LINK_LIBRARIES(${appname} ${FRAMEWORK_${fwname}})
    MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
endif()
endmacro(ADD_FRAMEWORK)


macro(source_group_by_dir source_files)       
	set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR}/)
	foreach(sgbd_file ${${source_files}})
		string(REGEX REPLACE ${sgbd_cur_dir} "" sgbd_fpath ${sgbd_file})
		string(REGEX REPLACE "[^/\\\\]+$" "" sgbd_group_name ${sgbd_fpath})
		if(sgbd_group_name)
			string(REPLACE "/"   "\\\\"  sgbd_group_name_normal ${sgbd_group_name})
			#message(STATUS ${sgbd_group_name_normal})
			source_group(${sgbd_group_name_normal} FILES ${sgbd_file})
		endif(sgbd_group_name)	
	endforeach(sgbd_file)
endmacro(source_group_by_dir)

add_subdirectory(ZegoLiveDemo)