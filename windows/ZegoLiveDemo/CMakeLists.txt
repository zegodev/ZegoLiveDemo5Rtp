cmake_minimum_required(VERSION 3.6)

#设置工程名称
project(ZegoLiveDemo)

#set(CMAKE_SKIP_BUILD_RPATH TRUE)                 # 编译时加上RPATH  
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

#注意：执行该Cmake之前，需要先在系统环境变量中设置好Qt路径。
#例如： 32位Qt的Key是QT_DIR， value是C:\Qt\Qt5.7.1\5.7\msvc2013（以Qt5.7.1为例）
#其他环境以此类推

if(WINDOWS_PLATFORM STREQUAL "x86")
    SET(CMAKE_PREFIX_PATH $ENV{QT_DIR})
elseif(WINDOWS_PLATFORM STREQUAL "x64")
    SET(CMAKE_PREFIX_PATH $ENV{QT_DIR_x64})
elseif(WINDOWS_PLATFORM STREQUAL "x86_xp")
	SET(CMAKE_PREFIX_PATH $ENV{QT_DIR_XP})
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS,5.01")
endif()

#添加qt库
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

#编译时自动打开moc
set(CMAKE_AUTOMOC ON)
#设置工程包含当前目录，非必须                    
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#添加.ui文件，并将通过qt5_wrap_ui将.ui文件包裹成ui_*.h文件
FILE(GLOB_RECURSE FORMS "*.ui")
QT5_WRAP_UI(FORMS_UIC ${FORMS})

#添加资源文件.qrc
FILE(GLOB RES "*.qrc")
QT5_ADD_RESOURCES(RES_RCC ${RES})

file(GLOB_RECURSE All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.mm 
                              ${CMAKE_CURRENT_LIST_DIR}/*.m 
                              ${CMAKE_CURRENT_LIST_DIR}/*.cpp 
                              ${CMAKE_CURRENT_LIST_DIR}/*.mm 
                              ${CMAKE_CURRENT_LIST_DIR}/*.c 
                              ${CMAKE_CURRENT_LIST_DIR}/*.cc 
                              ${CMAKE_CURRENT_LIST_DIR}/*.hh 
                              ${CMAKE_CURRENT_LIST_DIR}/*.h)
            
if(WIN32)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/OSX_Objective-C/ZegoAVDevice.h)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/OSX_Objective-C/ZegoAVDevice.mm)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/OSX_Objective-C/ZegoCGImageToQImage.h)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/OSX_Objective-C/ZegoCGImageToQImage.mm)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/OSX_Objective-C/ZegoViewZoom.h)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/OSX_Objective-C/ZegoViewZoom.mm)
    if(NOT WINDOWS_PLATFORM STREQUAL "x86")
        list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/AudioHookDialog/ZegoMusicHookDialog.h)
        list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/AudioHookDialog/ZegoMusicHookDialog.cpp)
        list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/SoftWareInfo/ZegoSoftWareInfo.h)
        list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/SoftWareInfo/ZegoSoftWareInfo.cpp)
        list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/Module/ZegoSurfaceMergeApi.h)
        list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/Module/ZegoSurfaceMergeApi.cpp)
    endif()
elseif(APPLE)
	list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/SoftWareInfo/ZegoSoftWareInfo.h)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/SoftWareInfo/ZegoSoftWareInfo.cpp)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/AudioHookDialog/ZegoMusicHookDialog.h)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/AudioHookDialog/ZegoMusicHookDialog.cpp)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/Module/ZegoSurfaceMergeApi.cpp)
    list(REMOVE_ITEM All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/Module/ZegoSurfaceMergeApi.cpp)
endif()

source_group_by_dir(All_SOURCES)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    include_directories(${CMAKE_CURRENT_LIST_DIR}/../include/zegoliveroom
                        ${CMAKE_CURRENT_LIST_DIR}
                        ${CMAKE_CURRENT_LIST_DIR}/UI)

    if(WINDOWS_PLATFORM STREQUAL "x86")
        include_directories(${CMAKE_CURRENT_LIST_DIR}/../include/zegosurfacemerge
                            ${CMAKE_CURRENT_LIST_DIR}/../include/zegoaudiohook
                            ${CMAKE_CURRENT_LIST_DIR}/AudioHookDialog)
    endif(WINDOWS_PLATFORM STREQUAL "x86")

elseif(APPLE)
    include_directories(${CMAKE_CURRENT_LIST_DIR}
                        ${CMAKE_CURRENT_LIST_DIR}/../libs/mac/ZegoLiveRoomOSX.framework/Versions/A/Headers
                        ${CMAKE_CURRENT_LIST_DIR}/UI)
endif()

set(SCRIPT_PATH ${CMAKE_CURRENT_LIST_DIR}/../..)

if(WIN32)
	set(exe_property WIN32)
    set(ZegoLiveDemo_RC ${CMAKE_CURRENT_LIST_DIR}/Resources/res.rc)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

    set(WATERPRINTS_PATH ${CMAKE_CURRENT_LIST_DIR}/Resources/images/waterprint)
    set(PCM_FILE_PATH ${CMAKE_CURRENT_LIST_DIR}/Resources/a.pcm)
    set(OPENSSL_PATH ${CMAKE_CURRENT_LIST_DIR}/openssl)

    if(WINDOWS_PLATFORM STREQUAL "x86")
    	set(LINK_LIBRARY zegoliveroom.lib ZegoSurfaceMerge.lib ZegoAudioHook.lib)
        set(ZEGOSURFACEMERGE_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/windows/x86/$(Configuration)/ZegoSurfaceMerge.dll)
        set(ZEGOAUDIOHOOK_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/windows/x86/$(Configuration)/ZegoAudioHook.dll)
        set(MUSICHOOK_PATH ${CMAKE_CURRENT_LIST_DIR}/MusicHook)
    else()
    	set(LINK_LIBRARY zegoliveroom.lib)
    endif()

	set(ZEGOLIVEROOM_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/windows/${WINDOWS_PLATFORM}/$(Configuration)/zegoliveroom.dll)
    set(MSVC_PATH ${CMAKE_CURRENT_LIST_DIR}/msvc/${WINDOWS_PLATFORM})
    add_definitions(-DUNICODE -D_UNICODE -D_SCL_SECURE_NO_WARNINGS -DWIN32 -DV_LOG -DCURL_STATICLIB)
    link_directories(${CMAKE_CURRENT_LIST_DIR}/../libs/windows/${WINDOWS_PLATFORM})

elseif(APPLE)
    SET(BUILD_WITH_INSTALL_RPATH TRUE)
    set(exe_property MACOSX_BUNDLE)
    set(MACOSX_BUNDLE_ICON_FILE ${CMAKE_CURRENT_LIST_DIR}/Resources/ZegoLiveDemo.icns)
    #set(ZegoLiveDemo_RC ${CMAKE_CURRENT_LIST_DIR}/Info.plist)
    set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    set(LINK_LIBRARY ${CMAKE_CURRENT_LIST_DIR}/../libs/mac/ZegoLiveRoomOSX.framework)				
    link_directories(${CMAKE_CURRENT_LIST_DIR}/../libs/mac)
endif(WIN32)

#构建可执行文件
set(NAME ZegoLiveDemo)
add_executable(${NAME} ${exe_property} ${All_SOURCES} ${ZegoLiveDemo_RC} ${FORMS_UIC} ${RES_RCC} ${MACOSX_BUNDLE_ICON_FILE} ${LangSrcs})



if(WIN32)
    #add_custom_command(TARGET ZegoLiveDemo PRE_BUILD COMMAND python ${SCRIPT_PATH}/setup-newest-zegoliveroom.py --config $(Configuration) --platform ${WINDOWS_PLATFORM})

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${ZEGOLIVEROOM_PATH} cmake -E copy ${ZEGOLIVEROOM_PATH} ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${OPENSSL_PATH}/${WINDOWS_PLATFORM}/libeay32.dll cmake -E copy ${OPENSSL_PATH}/${WINDOWS_PLATFORM}/libeay32.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${OPENSSL_PATH}/${WINDOWS_PLATFORM}/ssleay32.dll cmake -E copy ${OPENSSL_PATH}/${WINDOWS_PLATFORM}/ssleay32.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${MSVC_PATH}/msvcp120.dll cmake -E copy ${MSVC_PATH}/msvcp120.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${MSVC_PATH}/msvcr120.dll cmake -E copy ${MSVC_PATH}/msvcr120.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${WATERPRINTS_PATH} cmake -E copy_directory ${WATERPRINTS_PATH} ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)/Resources/waterprint)

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${WATERPRINTS_PATH} cmake -E copy_directory ${WATERPRINTS_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Resources/waterprint)

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${PCM_FILE_PATH} cmake -E copy ${PCM_FILE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)/Resources/a.pcm)

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${PCM_FILE_PATH} cmake -E copy ${PCM_FILE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Resources/a.pcm)

    if(WINDOWS_PLATFORM STREQUAL "x86")
        add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${ZEGOSURFACEMERGE_PATH} cmake -E copy ${ZEGOSURFACEMERGE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

        add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${ZEGOAUDIOHOOK_PATH} cmake -E copy ${ZEGOAUDIOHOOK_PATH} ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

        add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${MUSICHOOK_PATH} cmake -E copy_directory ${MUSICHOOK_PATH} ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)/MusicHook)

        add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND if exist ${MUSICHOOK_PATH} cmake -E copy_directory ${MUSICHOOK_PATH} ${CMAKE_CURRENT_BINARY_DIR}/MusicHook)
    endif()    

elseif(APPLE)
    set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/Resources/ZegoLiveDemo.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_target_properties(${NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE ZegoLiveDemo.icns)
    
    #add_custom_command(TARGET ZegoLiveDemo PRE_BUILD COMMAND python ${SCRIPT_PATH}/setup-newest-zegoliveroom.py)

    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND cp ${CMAKE_CURRENT_LIST_DIR}/Resources/images/waterprint/WaterPrint.png ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/ZegoLiveDemo.app/Contents/Resources/WaterPrint.png)
    
    add_custom_command(TARGET ZegoLiveDemo POST_BUILD COMMAND cp ${CMAKE_CURRENT_LIST_DIR}/Resources/images/waterprint/WaterPrint@2x.png ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/ZegoLiveDemo.app/Contents/Resources/WaterPrint@2x.png)
    
    ADD_FRAMEWORK(Foundation ZegoLiveDemo)
    ADD_FRAMEWORK(AVFoundation ZegoLiveDemo)
    ADD_FRAMEWORK(cocoa ZegoLiveDemo)
    ADD_FRAMEWORK(CoreMedia ZegoLiveDemo)
    ADD_FRAMEWORK(CoreVideo ZegoLiveDemo)

    #set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT dwarf-with-dsym)
    set_target_properties(ZegoLiveDemo PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
    set_target_properties(ZegoLiveDemo PROPERTIES XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS "YES")

    set_target_properties(ZegoLiveDemo PROPERTIES XCODE_ATTRIBUTE_SEPARATE_STRIP "YES")
    set_target_properties(ZegoLiveDemo PROPERTIES XCODE_ATTRIBUTE_STRIP_STYLE "Non-Global Symbols")

endif(WIN32)

qt5_use_modules(${NAME} Core)
qt5_use_modules(${NAME} Gui)
qt5_use_modules(${NAME} Widgets)
qt5_use_modules(${NAME} Network)

target_link_libraries(${NAME} ${LINK_LIBRARY})



