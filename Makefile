OBJS = src/main.cpp src/Vector.cpp src/Sphere.cpp src/RGB.cpp \
       src/Plane.cpp src/GameObject.cpp src/Light.cpp src/Image.cpp \
       src/Camera.cpp

#compiler we're using
CC = g++

#additional compilation options
COMPILER_FLAGS = -w

#libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#these are only used for debug
DEBUG_FLAGS = -pg

#specifies the name of our executable
OBJ_NAME = raytracer

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

.PHONY : clean
clean :
	rm $(OBJ_NAME)




