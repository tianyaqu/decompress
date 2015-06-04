LINKER      =        g++
DESTDIR_TARGET = liblzma.dll
TARGET = liblzma.a
LFLAGS        =        -Wl,-s -shared -Wl,-subsystem,console -mthreads -Wl,--out-implib,$(TARGET)
CFLAGS        = -pipe -fno-keep-inline-dllexport -O2 -Wall -Wextra $(DEFINES)
CXXFLAGS      = -pipe -fno-keep-inline-dllexport -O2 -frtti -Wall -Wextra -fexceptions -mthreads $(DEFINES)
COPY          = cp -f
DEL_FILE      = rm -f

SOURCES = \
    7zAlloc.c \
    7zBuf.c \
    7zBuf2.c \
    7zCrc.c \
    7zCrcOpt.c \
    7zDec.c \
    7zFile.c \
    7zIn.c \
    7zStream.c \
    Alloc.c \
    Bcj2.c \
    Bra.c \
    Bra86.c \
    BraIA64.c \
    CpuArch.c \
    Delta.c \
    LzFind.c \
    LzFindMt.c \
    Lzma2Dec.c \
    Lzma2Enc.c \
    Lzma86Dec.c \
    Lzma86Enc.c \
    LzmaDec.c \
    LzmaEnc.c \
    LzmaLib.c \
    MtCoder.c \
    Ppmd7.c \
    Ppmd7Dec.c \
    Ppmd7Enc.c \
    Sha256.c \
    Threads.c \
    Xz.c \
    XzCrc64.c \
    XzDec.c \
    XzEnc.c \
    XzIn.c 

OBJECTS = 7zAlloc.o 7zBuf.o 7zBuf2.o 7zCrc.o 7zCrcOpt.o 7zDec.o 7zFile.o 7zIn.o 7zStream.o Alloc.o Bcj2.o Bra.o \
    Bra86.o BraIA64.o CpuArch.o Delta.o LzFind.o LzFindMt.o Lzma2Dec.o Lzma2Enc.o Lzma86Dec.o Lzma86Enc.o LzmaDec.o LzmaEnc.o \
    LzmaLib.o MtCoder.o Ppmd7.o Ppmd7Dec.o Ppmd7Enc.o Sha256.o Threads.o Xz.o XzCrc64.o XzDec.o XzEnc.o XzIn.o    

all: $(DESTDIR_TARGET)

$(DESTDIR_TARGET):  $(OBJECTS) 
	$(LINKER) $(LFLAGS) -o $(DESTDIR_TARGET) $(OBJECTS)
	$(COPY) $(TARGET) ../
	$(COPY) $(DESTDIR_TARGET) ../
    
clean: 
	-$(DEL_FILE) $(OBJECTS) $(DESTDIR_TARGET) $(TARGET) 
	-$(DEL_FILE) ../$(TARGET) 