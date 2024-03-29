#Intended for an MSYS2 environment if being compiled on Windows
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(ARCH "x86_64")
cmake_policy(SET CMP0100 NEW)
if(WIN32 OR WIN64)
	add_definitions(-DWINDOWS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++20 -Wall -Wextra -Wpedantic -Wformat-security -Wno-unused")
	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(ARCH "x86_64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FORTIFY_SOURCE=2 -fPIE -mwindows")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--high-entropy-va -Wl,--dynamicbase -Wl,--nxcompat -Wl,-Bstatic -s")
	elseif(CMAKE_BUILD_TYPE MATCHES Debug)
		message(STATUS "Hardening disabled for debug build")
	endif()
elseif(UNIX)
	add_definitions(-DLINUX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Wpedantic -Wformat-security -Wno-unused")
	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fPIE")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,high-entropy-va")
	elseif(CMAKE_BUILD_TYPE MATCHES Debug)
		message(STATUS "Hardening disabled for debug build")
	endif()
elseif(APPLE)
	add_definitions(-DOSX)
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
	set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
	add_definitions(-DRELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0")
	add_definitions(-DDEBUG)
endif()

add_subdirectory(libcommons)
include_directories("libcommons/src/")

set(SRC
		src/main.cc
		
		src/graphics/color.cc src/graphics/color.hh
		src/graphics/filter.hh
		src/graphics/image.cc src/graphics/image.hh
		src/graphics/png.cc src/graphics/png.hh
		
		src/util/globals.hh src/util/globals.cc
		src/util/io.cc src/util/io.hh
		src/util/tools.hh
		src/util/def.hh
		src/util/threadPool.cc src/util/threadPool.hh
		src/util/util.cc src/util/util.hh
		src/util/gui.cc src/util/gui.hh
		
		src/widgets/mainWindowWidget.cc src/widgets/mainWindowWidget.hh
		src/widgets/pickColorButton.cc src/widgets/pickColorButton.hh
		src/widgets/brushToolButton.cc src/widgets/brushToolButton.hh
		src/widgets/eraserToolButton.cc src/widgets/eraserToolButton.hh
		src/widgets/eyedropperToolButton.cc src/widgets/eyedropperToolButton.hh
		src/widgets/fillToolButton.cc src/widgets/fillToolButton.hh
		src/widgets/workspaceWidget.cc src/widgets/workspaceWidget.hh)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++") #TODO this isn't working under MSYS2
project(NovaPx)
include_directories(include)
set(CMAKE_AUTOMOC ON)

add_definitions(-DQT6)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
if(WIN32 OR WIN64)
	set(LIBS Qt6::Widgets -lpng -lz -lgif)
elseif(UNIX)
	set(LIBS Qt6::Widgets png z dl pthread gif)
endif()

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${LIBS})
