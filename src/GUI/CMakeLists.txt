cmake_minimum_required(VERSION 3.28)

set(PACKAGE_NAME "gui" CACHE INTERNAL "Package name")

project(${PACKAGE_NAME})

set(SOURCE_FILES
  main.cpp
  appCore.cpp
  cpp/CanvasController.cpp
  qml.qrc
)

message(${CMAKE_CURRENT_BINARY_DIR})

find_package(PkgConfig REQUIRED)

set(CORE_TARGET core)
if(NOT TARGET core)
  find_package(core REQUIRED)
  set(CORE_TARGET core::core)
endif()

find_package(Qt5 COMPONENTS Core Gui Qml Quick  REQUIRED)

qt5_add_resources(APP_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/qml.qrc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_executable(${PACKAGE_NAME} ${APP_RESOURCES} ${SOURCE_FILES})

target_include_directories(${PACKAGE_NAME}
                           PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")


target_link_libraries(${PACKAGE_NAME}
                      Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick ${CORE_TARGET})

install(TARGETS ${PACKAGE_NAME}
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT runtime
)
