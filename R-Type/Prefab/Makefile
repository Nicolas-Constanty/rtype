# Sample makefile
# see also http://bojan-komazec.blogspot.fr/2011/10/how-to-use-nmake-and-makefile.html
  
!include <win32.mak>

#define macros
EXECUTABLE_NAME = Monster.dll
DIR_SRC = ..\..\src\Monster
DIR_INCLUDE = ..\..\include
DEPENDENCIES_INCLUDE = ..\..\Dependencies\SFML\Win\include
DIR_BIN = ..\bin
DIR_BIN_X86 = $(DIR_BIN)\x86
DIR_INTERMEDIATE = ..\intermediate
DIR_INTERMEDIATE_X86 = $(DIR_INTERMEDIATE)\x86

LIB_ENGINE = ..\x64\Debug\SaltyEngine.lib

SRC_FILES= \
  $(DIR_SRC)\Monster.cpp \
  $(DIR_SRC)\MonsterController.cpp

# description block
$(EXECUTABLE_NAME) : $(SRC_FILES)
	@echo "finding at path $(DIR_INCLUDE)"
  cl /EHsc /I$(DIR_INCLUDE) /I$(DEPENDENCIES_INCLUDE) $(SRC_FILES) /MDd /D MONSTER_EXPORTS /link $(LIB_ENGINE) /DLL /out:$(EXECUTABLE_NAME)
  copy *.obj $(DIR_INTERMEDIATE_X86)
  del *.obj

# build application
helloworld: $(EXECUTABLE_NAME)

# create output directories
create_dirs:
 @if not exist $(DIR_BIN_X86) mkdir $(DIR_BIN_X86)
 @if not exist $(DIR_INTERMEDIATE_X86) mkdir $(DIR_INTERMEDIATE_X86)

# delete output directories
clean:
 @if exist $(DIR_BIN) rmdir /S /Q $(DIR_BIN)
 @if exist $(DIR_INTERMEDIATE) rmdir /S /Q $(DIR_INTERMEDIATE)
 del $(EXECUTABLE_NAME)

# create directories and build application
all: clean create_dirs helloworld
