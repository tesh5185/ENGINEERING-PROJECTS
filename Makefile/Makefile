-include sources.mk

ifeq ($(TARGET),bbb)
	CC=arm-linux-gnueabihf-gcc
else ifeq ($(TARGET),frdm)
	CC=arm-none-eabi-gcc
else
	CC=gcc
endif

CFLAGS=-c -g -O0
SOURCES=./src/main.c ./src/data.c ./src/project_1.c ./src/memory.c 
OBJ_FILES=$(SOURCES:.c=.o)
PREPROC_FILES=$(SOURCES:.c=.i)
ASM_FILES=$(SOURCES:.c=.S)
EXECUTABLE=project
STATIC_LIBRARY=libproject1.a

.PHONY : all

%.i: %.c 
	$(CC) -E -o $@ $< $(INC_DIR)

%.S: %.c 
	$(CC) -S -o $@ $< $(INC_DIR)

%.o: %.c 
	$(CC) $(CFLAGS) -o $@ $< $(INC_DIR)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(INC_DIR) $^ -o $@
	objdump -Sx ./src/main.o ./src/data.o ./src/project_1.o ./src/memory.o >project.asm 

build-lib: project
	ar rcs $(STATIC_LIBRARY) ./src/main.o ./src/data.o ./src/project_1.o ./src/memory.o
	@echo 'Running size tool'	
	$(CC)-size project
	@echo ' '

preprocess: $(PREPROC_FILES)
	echo "Generating preprocessor files"

asm-files: $(ASM_FILES)
	echo "Generating asm files"

compile-all: $(OBJ_FILES)
	echo "Compiling all files"

upload:
	sh upload_files_to_bbg.sh

clean:
	rm -rf ./src/*.o project
