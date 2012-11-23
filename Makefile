
################################
#
# other libraries needed 
#

################################

CC=gcc
CFLAGS=-c -Wall -O2
LDFLAGS=-D_IOLIB=2 -D_FILE_OFFSET_BITS=64 #-D_NO_RAZF #-D_NO_CURSES

INCLUDES=-I. 
LIBDIRS=-L. 
LIBS= -lm 

SOURCES=InputData.c OutputData.c dbSNP_misc.c main.c
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)
EXECUTABLE=qjjpipeline

all:$(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE):$(OBJECTS)
	$(CC)  $(LDFLAGS) $(INCLUDES) $(LIBDIRS) $(OBJECTS) -o $@ $(LIBS)

cp: 
	cp $(EXECUTABLE) ~/bin

clean: 
	rm *.o $(EXECUTABLE)

