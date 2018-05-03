GLM_PATH  = ../ext/glm-0.9.4.1

TEMPLATE  = app
TARGET    = Projet

LIBS     += -lGLEW -lGL -lGLU -lm
INCLUDEPATH  += $${GLM_PATH}

SOURCES   = shader.cpp  trackball.cpp camera.cpp main.cpp viewer.cpp grid.cpp
HEADERS   = shader.h  trackball.h quat.h camera.h viewer.h grid.h vec4.h vec3.h vec2.h mat3.h mat4.h

CONFIG   += qt opengl warn_on thread uic4 release
QT       *= xml opengl core
