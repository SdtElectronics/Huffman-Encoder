CPP=g++
CFLAGS=-std=c++11 -Wall -I. -IDeviceHandlers -fopenmp -std=c++17 -lstdc++
#CFLAGS=-std=c++11 -g3 -Wall -I. -IDeviceHandlers 
OUT=HuffmanEncoder
OUTDIR=../out
OBJDIR=../out/obj
LIB=lib/

_OBJ=$(LIB)HTF.cxx $(LIB)llogger.cxx $(LIB)parRead.cxx $(LIB)parWdCnt.cxx main.o

OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

INC=$(LIB)HTF.h $(LIB)llogger.h $(LIB)parRead.h $(LIB)parWdCnt.h $(LIB)utils.h version.h\

all: credirs build

$(OBJ): $(OBJDIR)/%.o: %.cxx $(INC) Makefile
	$(CPP) $< -c -o $@ $(CFLAGS)

credirs:
	mkdir -p $(OUTDIR)
	mkdir -p $(OBJDIR)
	
build: $(OBJ)
	$(CPP) -o $(OUTDIR)/$(OUT) $^ -lconfig -lpthread

clean:
	rm -R -f $(OBJDIR)
	rm -R -f $(OUTDIR)
