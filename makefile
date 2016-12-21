CC = g++
CFLAGS = -std=c++11

RENDERER := \
src/Vector.cpp\
src/Matrix.cpp \
src/Color.cpp \
src/Vertex.cpp \
src/Texture.cpp \
src/Mesh.cpp \
src/Renderer.cpp \
main.cpp

SRC := $(RENDERER)

TARGET := main

main : 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)