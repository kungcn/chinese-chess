cmake_minimum_required(VERSION 3.7)
project(Chinese_Chess)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Header.h main.cpp
        Shader.cpp Shader.h
        Camera.cpp Camera.h
        Model.cpp Model.h
        Defination.h
        Callback.cpp Callback.h Defination.cpp auxiliary.cpp auxiliary.h Mesh.cpp Mesh.h Object.cpp Object.h Light.cpp Light.h ChessBoard.cpp ChessBoard.h Chess.cpp Chess.h)

add_executable(Chinese_Chess ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} glut)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLU)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLEW)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GL)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} dl)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} X11)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xrandr)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xi)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xxf86vm)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xinerama)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Xcursor)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} pthread)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} SOIL)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} assimp)