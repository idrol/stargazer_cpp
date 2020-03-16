cmake_minimum_required(VERSION 3.8)
project(stargazer)

find_package(OpenGL REQUIRED)

include_directories(Dependencies/glfw-3.2.1/include)
include_directories(Dependencies/glew-2.1.0/include)
include_directories(Dependencies/assimp-4.1.0/include)
include_directories(Dependencies/glm/include)
include_directories(Dependencies/boost-1.65.1/include)
include_directories(Dependencies/bullet3-2.87/include)
include_directories(Dependencies/json-3.1.1/include)
include_directories(Dependencies/mono-2.0/include)
#include_directories(Dependencies/spdlog-0.14.0/include)

include(Source/RenderEngine/CMakeLists.txt)
include(Source/RenderEngine/Command/CMakeLists.txt)
include(Source/RenderEngine/Model/CMakeLists.txt)
include(Source/RenderEngine/Shaders/CMakeLists.txt)
include(Source/RenderEngine/PostProcessing/CMakeLists.txt)
include(Source/ResourceManager/CMakeLists.txt)
include(Source/Lib/CMakeLists.txt)
include(Source/Input/CMakeLists.txt)
include(Source/GUI/CMakeLists.txt)
include(Source/Util/CMakeLists.txt)
include(Source/Physics/CMakeLists.txt)
include(Source/Engine/CMakeLists.txt)
include(Source/Engine/Scripting/CMakeLists.txt)
include(Source/Editor/CMakeLists.txt)
include(Source/CAPI/CMakeLists.txt)

set_source_files_properties(${stargazer_CAPI} PROPERTIES CMAKE_EXE_LINKER_FLAGS -rdynamic)

set(SOURCE_FILES ${stargazer_SOURCES} "Source/StargazerEngine.h" ${stargazer_CAPI})

source_group(TREE ${CMAKE_SOURCE_DIR}/Source FILES ${SOURCE_FILES})

set(VS_LIBS_DEBUG_64 
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/Bullet3Common_Debug.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/BulletCollision_Debug.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/BulletDynamics_Debug.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/BulletInverseDynamics_Debug.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/BulletSoftBody_Debug.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/LinearMath_Debug.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/boost_chrono-vc141-mt-gd-1_65_1.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/boost_date_time-vc141-mt-gd-1_65_1.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/boost_system-vc141-mt-gd-1_65_1.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/boost_thread-vc141-mt-gd-1_65_1.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/boost_filesystem-vc141-mt-gd-1_65_1.lib
		${CMAKE_SOURCE_DIR}/lib/x64/msvc/assimp-vc140-mt.lib
        ${CMAKE_SOURCE_DIR}/lib/x64/msvc/glew32d.lib
        ${CMAKE_SOURCE_DIR}/lib/x64/msvc/glfw3dll.lib
		${MONO_LIBRARIES}
		opengl32
)

set(MINGW_LIBS_DEBUG_64
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libBullet3Common.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libBulletCollision.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libBulletDynamics.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libBulletInverseDynamics.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libBulletSoftBody.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libLinearMath.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libboost_chrono-mgw72-mt-d-1_65_1.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libboost_date_time-mgw72-mt-d-1_65_1.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libboost_system-mgw72-mt-d-1_65_1.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libboost_thread-mgw72-mt-d-1_65_1.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libboost_filesystem-mgw72-mt-d-1_65_1.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libassimp.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libglew32d.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libglfw3dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libMonoPosixHelper.dll.a
		${CMAKE_SOURCE_DIR}/lib/x64/mingw/libmonosgen-2.0.dll.a
		opengl32
)

set(VS_LIBS_RELEASE_64 
		opengl32
)

add_executable(stargazer ${SOURCE_FILES})

add_compile_options(${MONO_CFLAGS_OTHER})

if(MSVC)
	target_link_libraries(stargazer ${VS_LIBS_DEBUG_64})
else()
	target_link_libraries(stargazer ${MINGW_LIBS_DEBUG_64})
endif()

#add_custom_command(TARGET stargazer PRE_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#                       ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:stargazer>/Assets)

if(MSVC)
	add_custom_command(TARGET stargazer PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/bin/x64/msvc $<TARGET_FILE_DIR:stargazer>)
else()
	add_custom_command(TARGET stargazer PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/bin/x64/mingw $<TARGET_FILE_DIR:stargazer>)
endif()