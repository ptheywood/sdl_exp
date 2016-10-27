# Executable file name
EXECUTABLE_FILE = sdl_exp
# Directories within the project
BUILD_DIR = build
SOURCE_DIR = sdl_exp
EXECUTABLE_DIR = bin
LIB_DIR = lib
INCLUDE_DIR = include

INCLUDE_SRC_DIRS = $(addprefix -I,$(shell find $(SOURCE_DIR) -type d))

# Define compiler and linker to use
CC = g++
LD = g++
# Default compiler and linker flags
CFLAGS = -c -Wall  $(INCLUDE_SRC_DIRS) -I$(INCLUDE_DIR) -std=c++14 -Wno-write-strings
LDFLAGS = -lGLEW -lGLU -lGL -lSDL2 -lSDL2_image -lpthread -lfreetype

# Find source files to compiler
SOURCES = $(shell find $(SOURCE_DIR) -type f -name '*.cpp')

VPATH = $(shell find $(SOURCE_DIR) -type d)

# Create list of object files in the build directory to be created.
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:=.o)))
# Get path to executable
EXECUTABLE=$(EXECUTABLE_DIR)/$(EXECUTABLE_FILE)

# Some targets are not files.
.PHONY: all prepare clean clean-objects clean-executable

# Default rule (all)
all: prepare $(SOURCES) $(EXECUTABLE)

# Rule for building executable from object files (linking)
$(EXECUTABLE): $(OBJECTS)
	$(LD)  $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Rule to compile cpp files to onbject files
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Ensure required directories exist
prepare:
	@mkdir -p $(BUILD_DIR) $(EXECUTABLE_DIR)

# Remove object and executable files.
clean: clean-objects clean-executable

# Remove build directory contents
clean-objects:
	rm -rf $(BUILD_DIR)/*

# Remove the executable file.
clean-executable:
	rm -f $(EXECUTABLE)
