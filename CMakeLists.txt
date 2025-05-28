cmake_minimum_required(VERSION 3.8)

project(Pine3D VERSION 0.1.0)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

add_definitions(-DCMAKE_POLICY_VERSION_MINIMUM=3.5)
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()

# Source files
## ------------------------------------------------ ##
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src)

set(PINE3D-MAIN
	${SRC_ROOT}/Pine3D.cpp
	)

source_group("Source Files" FILES ${PINE3D-MAIN})

set(PINE3D-CORE
	${SRC_ROOT}/Core/Application.cpp
	${SRC_ROOT}/Core/Application.h
	${SRC_ROOT}/Core/Sfsf.h
	${SRC_ROOT}/Core/Window.cpp
	${SRC_ROOT}/Core/Window.h
	)
	
source_group("Source Files/Core" FILES ${PINE3D-CORE})

set(PINE3D-CORE-INPUT
	${SRC_ROOT}/Input/InputHandler.cpp
	${SRC_ROOT}/Input/InputHandler.h
	${SRC_ROOT}/Input/KeyCodes.h
	${SRC_ROOT}/Input/InputDevices.h
	${SRC_ROOT}/Input/InputState.h
	${SRC_ROOT}/Input/InputState.cpp
	${SRC_ROOT}/Input/MouseButtons.h
	)
	
source_group("Source Files/Input" FILES ${PINE3D-CORE-INPUT})

set(PINE3D-PLATFORM-OPENGL
	${SRC_ROOT}/Platform/OpenGL/OpenGLRenderer.cpp
	${SRC_ROOT}/Platform/OpenGL/OpenGLRenderer.h
	${SRC_ROOT}/Platform/OpenGL/GLFWWindow.cpp
	${SRC_ROOT}/Platform/OpenGL/GLFWWindow.h
	)
	
source_group("Source Files/Platform/OpenGL" FILES ${PINE3D-PLATFORM-OPENGL})

set(PINE3D-PLATFORM-IMGUI
	${SRC_ROOT}/Platform/ImGui/EditorImGui.cpp
	${SRC_ROOT}/Platform/ImGui/EditorImGui.h
	)
	
source_group("Source Files/Platform/ImGui" FILES ${PINE3D-PLATFORM-IMGUI})

set(PINE3D-EDITOR
	${SRC_ROOT}/Editor/EditorGUI.cpp
	${SRC_ROOT}/Editor/EditorGUI.h
	${SRC_ROOT}/Editor/Editor.cpp
	${SRC_ROOT}/Editor/Editor.h
	)
	
source_group("Source Files/Editor" FILES ${PINE3D-EDITOR})

set(PINE3D-RUNTIME-CAMERA
	${SRC_ROOT}/Runtime/Camera/Camera.cpp
	${SRC_ROOT}/Runtime/Camera/Camera.h
	)
	
source_group("Source Files/Runtime/Camera" FILES ${PINE3D-RUNTIME-CAMERA})

set(PINE3D-RUNTIME-COMPONENTS
	${SRC_ROOT}/Runtime/Components/Component.h
	${SRC_ROOT}/Runtime/Components/Cube.cpp
	${SRC_ROOT}/Runtime/Components/Cube.h
	${SRC_ROOT}/Runtime/Components/Image.cpp
	${SRC_ROOT}/Runtime/Components/Image.h
	${SRC_ROOT}/Runtime/Components/InputListener.cpp
	${SRC_ROOT}/Runtime/Components/InputListener.h
	${SRC_ROOT}/Runtime/Components/Material.cpp
	${SRC_ROOT}/Runtime/Components/Material.h
	${SRC_ROOT}/Runtime/Components/Mesh.cpp
	${SRC_ROOT}/Runtime/Components/Mesh.h
	${SRC_ROOT}/Runtime/Components/MeshRenderer.cpp
	${SRC_ROOT}/Runtime/Components/MeshRenderer.h
	${SRC_ROOT}/Runtime/Components/Polygon.cpp
	${SRC_ROOT}/Runtime/Components/Polygon.h
	${SRC_ROOT}/Runtime/Components/Texture.cpp
	${SRC_ROOT}/Runtime/Components/Texture.h
	${SRC_ROOT}/Runtime/Components/Transform.cpp
	${SRC_ROOT}/Runtime/Components/Transform.h
	)
	
source_group("Source Files/Runtime/Components" FILES ${PINE3D-RUNTIME-COMPONENTS})

set(PINE3D-RUNTIME-RENDERCORE
	${SRC_ROOT}/Runtime/RenderCore/Shader.cpp
	${SRC_ROOT}/Runtime/RenderCore/Shader.h
	)
	
source_group("Source Files/Runtime/RenderCore" FILES ${PINE3D-RUNTIME-RENDERCORE})

set(PINE3D-RUNTIME-RENDERER
	${SRC_ROOT}/Runtime/Renderer/Renderer.cpp
	${SRC_ROOT}/Runtime/Renderer/Renderer.h
	)
		
source_group("Source Files/Runtime/Renderer" FILES ${PINE3D-RUNTIME-RENDERER})

set(PINE3D-RUNTIME-SCENE
	${SRC_ROOT}/Runtime/Scene/SceneObject.h
	)

source_group("Source Files/Runtime/Scene" FILES ${PINE3D-RUNTIME-SCENE})

set(PINE3D-UTILS
	${SRC_ROOT}/Utils/Utils.h
	)
	
source_group("Source Files/Utils" FILES ${PINE3D-UTILS})

add_executable(${PROJECT_NAME} WIN32 
	${PINE3D-MAIN}
	${PINE3D-CORE}
	${PINE3D-CORE-INPUT}
	${PINE3D-EDITOR}
	${PINE3D-PLATFORM-IMGUI}
	${PINE3D-PLATFORM-OPENGL}
	${PINE3D-RUNTIME-CAMERA}
	${PINE3D-RUNTIME-COMPONENTS}
	${PINE3D-RUNTIME-RENDERCORE}
	${PINE3D-RUNTIME-RENDERER}
	${PINE3D-RUNTIME-SCENE}
	${PINE3D-UTILS}
	)

set(STD_INCLUDE 
	${PROJECT_SOURCE_DIR}/include/STB
	)

set(IMGUI_INCLUDE
	${PROJECT_SOURCE_DIR}/include/imgui
	)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SRC_ROOT} ${STD_INCLUDE} ${IMGUI_INCLUDE})
## ------------------------------------------------ ##

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw libglew_static glm)

# set Pine3D target as a startup project
if( MSVC )
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()