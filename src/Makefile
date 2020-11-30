CPP=g++
CFLAGS=-Wall -I. -I lib/ -fopenmp -std=c++17 -lstdc++ 
OUT=HuffmanEncoder
OUTDIR=../out
OBJDIR=../out/obj
LIB=lib/

_OBJ=$(LIB)HTF.o $(LIB)llogger.o $(LIB)parRead.o $(LIB)parWdCnt.o $(LIB)CODEC.o $(LIB)HFD.o $(LIB)codeFactory.o main.o

OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

INC=$(LIB)HTF.h $(LIB)llogger.h $(LIB)parRead.h $(LIB)parWdCnt.h $(LIB)CODEC.h $(LIB)HFD.h $(LIB)utils.h version.h\

all: credirs build

$(OBJ): $(OBJDIR)/%.o: %.cxx $(INC) Makefile
	$(CPP) $< -c -o $@ $(CFLAGS)

credirs:
	mkdir -p $(OUTDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/lib
	
build: $(OBJ)
	$(CPP) -o $(OUTDIR)/$(OUT) $^ -lconfig -lpthread

clean:
	rm -R -f $(OBJDIR)
	rm -R -f $(OUTDIR)
