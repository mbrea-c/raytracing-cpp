OBJS = src/main.cpp src/vector.cpp src/sphere.cpp src/RGB.cpp \
       src/plane.cpp src/object.cpp src/light.cpp src/Image.h \
       src/Image.cpp

#compiler we're using
CC = g++

#additional compilation options
COMPILER_FLAGS = -w

#libraries we're linking against
LINKER_FLAGS = -lSDL2

#specifies the name of our executable
OBJ_NAME = raytracer

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

.PHONY : clean
clean :
	rm $(OBJ_NAME)




