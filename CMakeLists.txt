cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(ARCH "x86_64")

if(WIN32 OR WIN64)
	add_definitions(-DWINDOWS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wno-unused")
	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(ARCH "x86_64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FORTIFY_SOURCE=2 -mmitigate-rop -fPIE")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--high-entropy-va -Wl,--dynamicbase -Wl,--nxcompat")
	elseif(CMAKE_BUILD_TYPE MATCHES Debug)
		message(STATUS "Hardening disabled for debug build")
	endif()
elseif(UNIX)
	add_definitions(-DLINUX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wno-unused")
	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(ARCH "x86_64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FORTIFY_SOURCE=2 -mmitigate-rop -fstack-protector-strong -fPIE")
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

set(SRC
		src/main.cc
		
		src/assets/shaders.hh
		src/assets/meshes.hh
		
		src/graphics/camera.hh
		src/graphics/color.cc src/graphics/color.hh
		src/graphics/fbo.cc src/graphics/fbo.hh
		src/graphics/filter.hh
		src/graphics/gl.cc src/graphics/gl.hh
		src/graphics/glad.c
		src/graphics/image.cc src/graphics/image.hh
		src/graphics/mesh.cc src/graphics/mesh.hh
		src/graphics/png.cc src/graphics/png.hh
		src/graphics/renderer.cc src/graphics/renderer.hh
		src/graphics/shader.cc src/graphics/shader.hh
		src/graphics/texture.cc src/graphics/texture.hh
		src/graphics/glWidget.cc src/graphics/glWidget.hh
		
		src/info/globals.hh src/info/globals.cc
		
		src/io/io.cc src/io/io.hh
		
		src/util/def.hh
		src/util/event.hh
		src/util/threadPool.cc src/util/threadPool.hh
		src/util/util.cc src/util/util.hh
		src/util/widget.cc src/util/widget.hh)

project(PixelCreator)
include_directories(include)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

if(WIN32 OR WIN64)
	set(LIBS
			Qt5::Widgets
			${CMAKE_SOURCE_DIR}/libs/libpng.a
			${CMAKE_SOURCE_DIR}/libs/libz.a)
elseif(UNIX)
	set(LIBS png z dl pthread)
endif()

include_directories(C:/msys64/mingw64/qt5-static/include/)
add_executable(${PROJECT_NAME} ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} ${LIBS})
