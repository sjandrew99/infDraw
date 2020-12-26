
srcdir=src

objdir=obj
incdir=include

OPENCV_LIBS = -lopencv_calib3d -lopencv_core -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_gapi -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_videoio -lopencv_video
OPENCV_INCDIRS = /usr/local/include/opencv4

cflags_gtk := $(shell pkg-config --cflags gtk+-3.0) 
cflags_gtk += -DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED
lflags_gtk := $(shell pkg-config --libs gtk+-3.0)

CC = g++
LIBS = $(OPENCV_LIBS)

INCDIRS = $(OPENCV_INCDIRS) .

Iincs := $(foreach inc,$(INCDIRS),-I$(inc))

cflags= -I$(incdir) -Wall -fmax-errors=1 -g -DDEBUG $(Ideps) $(Iincs) $(cflags_gtk) -I/usr/include/eigen3
pycflags= -I$(incdir) $(Iincs) $(cflags_gtk) -I/usr/include/eigen3

#linker flags:
LFLAGS = $(LIBS) $(LIBDIRS) -g $(lflags_gtk) #-L/home/steve/build/opencv/build/lib

#get list of src and corresponding object files
ALL_OBJS := $(patsubst $(srcdir)/%.cpp, $(objdir)/%.o, $(wildcard $(srcdir)/*.cpp))


#targets:
.PHONY: all clean

all : infDraw
	@echo "make done"

infDraw: $(ALL_OBJS)
	@echo ""
	@echo "building infDraw"
	$(CC) $(ALL_OBJS) -o $@ $(LFLAGS) -lgthread-2.0 -lpthread


$(objdir)/%.o : $(srcdir)/%.cpp
	$(CC) $(cflags) -c $< -o $@

clean :
	@echo "make -f ./makefile clean"
	rm -f infDraw $(ALL_OBJS)
	$(foreach dlib, $(deplibs), cd $(dir $(dlib)) && make clean) 
