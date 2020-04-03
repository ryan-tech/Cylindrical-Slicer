cmake_minimum_required(VERSION 3.3)

# Setting -std=c++11
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

# Set the version number
set (Slicer_VERSION_MAJOR "0")
set (Slicer_VERSION_MINOR "0")
set (Slicer_VERSION_PATCH "0")
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


install(TARGETS Slicer RUNTIME DESTINATION bin)

set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")


include(CPack)
