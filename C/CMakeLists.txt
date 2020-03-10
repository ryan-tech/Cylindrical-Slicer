cmake_minimum_required(VERSION 3.3)

# Setting -std=c++11
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

# Set the version number
set (Slicer_VERSION_MAJOR "0")
set (Slicer_VERSION_MINOR "9")
set (Slicer_VERSION_PATCH "3")
set (PROJECT_VERSION "${Slicer_VERSION_MAJOR}.${Slicer_VERSION_MINOR}.${Slicer_VERSION_PATCH}")

project(slicer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

#set project sources
set(Project_Sources src/app.cpp
src/backdrop.cpp
src/canvas.cpp
src/glmesh.cpp
src/loader.cpp
src/main.cpp
src/mesh.cpp
src/window.cpp)

#set project headers. 
set(Project_Headers src/app.h
src/backdrop.h
src/canvas.h
src/glmesh.h
src/loader.h
src/mesh.h
src/window.h)

#set project resources and icon resource
set(Project_Resources qt/qt.qrc gl/gl.qrc)
set(Icon_Resource exe/slicer.rc)

#set Policy CMP0072 FindOpenGL behavior
set(OpenGL_GL_PREFERENCE GLVND)

#find required packages. 
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

#add resources to RCC
qt5_add_resources(Project_Resources_RCC ${Project_Resources})

#tell CMake AUTOGEN to skip autogen on the generated qrc files
set_property(SOURCE ${Project_Resources_RCC} PROPERTY SKIP_AUTOGEN ON)

#include opengl files. 
include_directories(${QT_QTOPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} )

add_executable(Slicer WIN32 ${Project_Sources} ${Project_Headers} ${Project_Resources_RCC} ${Icon_Resource})
target_link_libraries(Slicer Qt5::Widgets Qt5::Core Qt5::Gui Qt5::OpenGL ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
if(WIN32)
  set(Slicer_LINK_FLAGS ${CMAKE_CURRENT_SOURCE_DIR}/${Icon_Resource})
  set_target_properties(Slicer PROPERTIES LINK_FLAGS ${Slicer_LINK_FLAGS})
endif(WIN32)

# Add version definitions to use within the code. 
target_compile_definitions(Slicer PRIVATE -DSlicer_VERSION="${PROJECT_VERSION}")

#installer information that is platform independent
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Cylindrical Slicer")
set(CPACK_PACKAGE_VERSION_MAJOR ${Slicer_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${Slicer_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${Slicer_VERSION_PATCH})

if(WIN32)

	set(QT_USE_QTMAIN true)
	
	if(MSVC)
		set_source_files_properties(Slicer PROPERTIES LINKER_LANGUAGE "CXX")
		set_target_properties(Slicer PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

		install(TARGETS Slicer DESTINATION bin COMPONENT all)
		
		install(FILES
			$<TARGET_FILE:Qt5::Gui_EGL>
			$<TARGET_FILE:Qt5::Gui_GLESv2>
			$<TARGET_FILE:Qt5::Core>
			$<TARGET_FILE:Qt5::Gui> 
			$<TARGET_FILE:Qt5::OpenGL>
			$<TARGET_FILE:Qt5::Widgets>
			DESTINATION bin COMPONENT all)
		
		#install file in the platforms directory.
		install (FILES
			${Qt5Core_DIR}/../../../plugins/platforms/qwindows.dll
			DESTINATION bin/platforms COMPONENT all
		)
		add_custom_command(TARGET Slicer POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core>       $<TARGET_FILE_DIR:${PROJECT_NAME}>
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui>        $<TARGET_FILE_DIR:${PROJECT_NAME}>
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets>    $<TARGET_FILE_DIR:${PROJECT_NAME}>
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::OpenGL>     $<TARGET_FILE_DIR:${PROJECT_NAME}>
		)	
	endif(MSVC)

	# windows specific installer generation information
	set(CPACK_GENERATOR NSIS)
	set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL OFF)
	set(CPACK_NSIS_MODIFY_PATH ON)
	set(CPACK_NSIS_MUI_FINISHPAGE_RUN ${PROJECT_NAME})
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
	set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\Slicer.exe")
	set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/ryan-tech/Cylindrical-Slicer")
	set(CPACK_NSIS_DISPLAY_NAME "Cylindrical Slicer ${Slicer_VERSION}")
	set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/exe/slicer.ico")
	set(CPACK_NSIS_MUI_UNIICON  "${CMAKE_CURRENT_SOURCE_DIR}/exe/slicer.ico")
	set(CPACK_NSIS_CREATE_ICONS_EXTRA
		"CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\slicer.lnk' '$INSTDIR\\\\bin\\\\slicer.exe'")
	set(CPACK_COMPONENTS_ALL all)
	if (CMAKE_CL_64)
		set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
	else (CMAKE_CL_64)
		set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
	endif (CMAKE_CL_64)
elseif(APPLE)
	set(CPACK_GENERATOR "DragNDrop")
	set(CPACK_DMG_FORMAT "UDBZ")
	set(CPACK_DMG_VOLUME_NAME "${PROJECT_NAME}")
	set(CPACK_SYSTEM_NAME "OSX")
	set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
    set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/app/slicer.icns")
else()
	install(TARGETS Slicer RUNTIME DESTINATION bin)

	set(CPACK_GENERATOR "DEB;RPM")
	set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
endif(WIN32)

include(CPack)
