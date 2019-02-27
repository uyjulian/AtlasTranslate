
CC = i686-w64-mingw32-gcc
CXX = i686-w64-mingw32-g++
AR = i686-w64-mingw32-ar
ASM = nasm
WINDRES = i686-w64-mingw32-windres
#CFLAGS += -O0 -gstabs
# GIT_HASH = $(shell git rev-parse --short HEAD)
GIT_TAG = $(shell git describe --abbrev=0 --tags)
ASMFLAGS += -fwin32 -DWIN32
CFLAGS += -Os -std=c++17
CFLAGS += -Wall -Wno-unused-value -Wno-format -fpermissive -I. -I.. -Ishared -DGIT_TAG=L\"$(GIT_TAG)\" -DNDEBUG -DWIN32 -D_WIN32 -D_WINDOWS 
CFLAGS += -D_USRDLL -DNO_ZLIB -DMINGW_HAS_SECURE_API -DUNICODE -D_UNICODE -DNO_STRICT -DCMAKE_INTDIR=\"Release\"   
LDFLAGS += -shared -static -static-libstdc++ -static-libgcc -Wl,--subsystem,windows -s 
LDLIBS += 

%.o: %.c
	echo -e "\tCC  $<"
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	echo -e "\tCXX  $<"
	$(CXX) -c $(CFLAGS) -o $@ $<

%.o: %.asm
	echo -e "\ASM  $<"
	$(ASM) $(ASMFLAGS) $< -o$@ 

%.o: %.rc
	echo -e "\tWINDRES  $<"
	$(WINDRES) --codepage=65001 $< $@

SOURCES := atlastranslate.cpp extensionimpl.cpp shared/Atlas.cpp shared/ConversionTable.cpp shared/ProcessUtil.cpp shared/Shrink.cpp shared/StringUtil.cpp shared/TextRuleSet.cpp shared/EUCJPtoUTF16.cpp
OBJECTS := $(SOURCES:.c=.o)
OBJECTS := $(OBJECTS:.cpp=.o)
OBJECTS := $(OBJECTS:.asm=.o)
OBJECTS := $(OBJECTS:.rc=.o)

BINARY ?= AtlasTranslate.dll
ARCHIVE ?= AtlasTranslate.$(GIT_TAG).7z

all: $(BINARY)

archive: $(ARCHIVE)

clean:
	rm -f $(OBJECTS) $(BINARY) $(ARCHIVE)

$(ARCHIVE): $(BINARY) ../LICENSE.GPLv2 ../LICENSE.GPLv3 ../README.md
	rm -f $(ARCHIVE)
	7z a $@ $^

$(BINARY): $(OBJECTS) 
	@echo -e "\tLNK $@"
	$(CXX) $(CFLAGS) $(LDFLAGS)  -o $@ $^  $(LDLIBS)
