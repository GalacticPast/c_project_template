ifeq ($(OS),Windows_NT)
	SHELL := cmd.exe
	
	SRC       := src
	BIN       := bin
	CC        := clang
	ASSEMBLY  :=  
	EXTENSION := .exe

	DIR := $(subst /,\,${CURDIR})
	INCLUDES  := 
# if raylib uncomment LINKER_FLAGS := -L./external/raylib/lib/windows/ -lraylib -lkernel32 -lgdi32 -luser32 -ladvapi32 -ltdh -lwinmm -lm 
	LINKER_FLAGS := 
	COMPILER_FLAGS := -Wall -Werror -Wextra -g -O0 -Wno-system-headers -Wno-unused-but-set-variable -Wno-unused-variable -Wno-varargs -Wno-unused-private-field -Wno-unused-parameter -Wno-unused-function -fsanitize=undefined -fsanitize-trap

	rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
	SRC_FILES := $(call rwildcard,$(SRC)/,*.c)

	DIRECTORIES := $(sort $(dir $(SRC_FILES)))
else
	SRC       := src
	BIN       := bin
	CC        := clang
	ASSEMBLY  := 
	EXTENSION := 

	INCLUDES     := 
# if raylib uncomment LINKER_FLAGS := -L./external/raylib/lib/windows/ -lraylib -lkernel32 -lgdi32 -luser32 -ladvapi32 -ltdh -lwinmm -lm 
	LINKER_FLAGS := 
	COMPILER_FLAGS := -Wall -Werror -Wextra -g -O0 -Wno-system-headers -Wno-unused-but-set-variable -Wno-unused-variable -Wno-varargs -Wno-unused-private-field -Wno-unused-parameter -Wno-unused-function -fsanitize=undefined -fsanitize-trap

	SRC_FILES := $(shell find $(SRC) -type f -name '*.c')
endif 

all: scaffold compile

scaffold:
ifeq ($(OS),Windows_NT)
	@if not exist $(BIN) mkdir $(BIN)
else
	@mkdir -p $(BIN)
endif

compile: 
ifeq ($(ASSEMBLY),)
	$(error Please name the executable. Variable ASSEMBLY is empty.)
else
	$(CC) $(SRC_FILES) $(COMPILER_FLAGS) -o $(BIN)/$(ASSEMBLY)$(EXTENSION) $(INCLUDES) $(LINKER_FLAGS)
endif
