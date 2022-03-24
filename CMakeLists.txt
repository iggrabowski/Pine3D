cmake_minimum_required( VERSION 3.8 )

project(Pine3D VERSION 0.1.0)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

# Source files
## ------------------------ ##
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(PINE3D-MAIN
	${SRCROOT}/Pine3D.cpp
	)

source_group("Source Files" FILES ${PINE3D-MAIN})

set(PINE3D-CORE
	${SRCROOT}/Core/Application.cpp
	${SRCROOT}/Core/Application.h
	${SRCROOT}/Core/Sfsf.h
	${SRCROOT}/Core/Window.cpp
	${SRCROOT}/Core/Window.h
	${SRCROOT}/Core/Controls.cpp
	${SRCROOT}/Core/Controls.h
	)
	
source_group("Source Files/Core" FILES ${PINE3D-CORE})

set(PINE3D-PLATFORM-OPENGL
	${SRCROOT}/Platform/OpenGL/OpenGLRenderer.cpp
	${SRCROOT}/Platform/OpenGL/OpenGLRenderer.h
	${SRCROOT}/Platform/OpenGL/GLFWWindow.cpp
	${SRCROOT}/Platform/OpenGL/GLFWWindow.h
	)
	
source_group("Source Files/Platform/OpenGL" FILES ${PINE3D-PLATFORM-OPENGL})

set(PINE3D-RUNTIME-CAMERA
	${SRCROOT}/Runtime/Camera/Camera.cpp
	${SRCROOT}/Runtime/Camera/Camera.h
	)
	
source_group("Source Files/Runtime/Camera" FILES ${PINE3D-RUNTIME-CAMERA})

set(PINE3D-RUNTIME-COMPONENTS
	${SRCROOT}/Runtime/Components/Cube.cpp
	${SRCROOT}/Runtime/Components/Cube.h
	${SRCROOT}/Runtime/Components/Material.cpp
	${SRCROOT}/Runtime/Components/Material.h
	${SRCROOT}/Runtime/Components/Mesh.cpp
	${SRCROOT}/Runtime/Components/Mesh.h
	${SRCROOT}/Runtime/Components/MeshRenderer.cpp
	${SRCROOT}/Runtime/Components/MeshRenderer.h
	${SRCROOT}/Runtime/Components/Polygon.cpp
	${SRCROOT}/Runtime/Components/Polygon.h
	${SRCROOT}/Runtime/Components/Texture.cpp
	${SRCROOT}/Runtime/Components/Texture.h
	${SRCROOT}/Runtime/Components/Transform.cpp
	${SRCROOT}/Runtime/Components/Transform.h
	)
	
source_group("Source Files/Runtime/Components" FILES ${PINE3D-RUNTIME-COMPONENTS})

set(PINE3D-RUNTIME-RENDERCORE
	${SRCROOT}/Runtime/RenderCore/Shader.cpp
	${SRCROOT}/Runtime/RenderCore/Shader.h
	)
	
source_group("Source Files/Runtime/RenderCore" FILES ${PINE3D-RUNTIME-RENDERCORE})

set(PINE3D-RUNTIME-RENDERER
	${SRCROOT}/Runtime/Renderer/Renderer.cpp
	${SRCROOT}/Runtime/Renderer/Renderer.h
	)
		
source_group("Source Files/Runtime/Renderer" FILES ${PINE3D-RUNTIME-RENDERER})

set(PINE3D-RUNTIME-SCENE
	${SRCROOT}/Runtime/Scene/SceneObject.h
	)

source_group("Source Files/Runtime/Scene" FILES ${PINE3D-RUNTIME-SCENE})

set(PINE3D-UTILS
	${SRCROOT}/Utils/Utils.h
	)
	
source_group("Source Files/Utils" FILES ${PINE3D-UTILS})

add_executable(${PROJECT_NAME} WIN32 
	${PINE3D-MAIN}
	${PINE3D-CORE}
	${PINE3D-PLATFORM-OPENGL}
	${PINE3D-RUNTIME-CAMERA}
	${PINE3D-RUNTIME-COMPONENTS}
	${PINE3D-RUNTIME-RENDERCORE}
	${PINE3D-RUNTIME-RENDERER}
	${PINE3D-RUNTIME-SCENE}
	${PINE3D-UTILS}
	)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SRCROOT})
## ------------------------ ##

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw libglew_static glm)

# set Pine3D target as a startup project
if( MSVC )
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()