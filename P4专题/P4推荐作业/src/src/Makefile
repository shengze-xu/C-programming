# Project: Pro01
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe -D__DEBUG__
CC       = gcc.exe -D__DEBUG__
WINDRES  = windres.exe
OBJ      = main.o anewmerge.o anewquick.o oldquick.o oldmerge.o
LINKOBJ  = main.o anewmerge.o anewquick.o oldquick.o oldmerge.o
LIBS     = -L"D:/myIDE/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32" -static-libgcc libpthreadGC2.a libpthreadGCE2.a pthreadVC2.lib pthreadVSE2.lib -m32 -g3
INCS     = -I"D:/myIDE/Dev-Cpp/MinGW64/include" -I"D:/myIDE/Dev-Cpp/MinGW64/x86_64-w64-mingw32/include" -I"D:/myIDE/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include"
CXXINCS  = -I"D:/myIDE/Dev-Cpp/MinGW64/include" -I"D:/myIDE/Dev-Cpp/MinGW64/x86_64-w64-mingw32/include" -I"D:/myIDE/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include" -I"D:/myIDE/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include/c++"
BIN      = Pro01.exe
CXXFLAGS = $(CXXINCS) -m32 -g3 -std=c99
CFLAGS   = $(INCS) -m32 -g3 -std=c99
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

anewmerge.o: anewmerge.c
	$(CC) -c anewmerge.c -o anewmerge.o $(CFLAGS)

anewquick.o: anewquick.c
	$(CC) -c anewquick.c -o anewquick.o $(CFLAGS)

oldquick.o: oldquick.c
	$(CC) -c oldquick.c -o oldquick.o $(CFLAGS)

oldmerge.o: oldmerge.c
	$(CC) -c oldmerge.c -o oldmerge.o $(CFLAGS)
