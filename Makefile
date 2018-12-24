# Output files
RELEASE_EXEC ?= bin/gltools
DEBUG_EXEC ?= bin/gltools-debug

# Directory controls
OBJ_DIR_BASE ?= build
OBJ_DIR_RELEASE ?= $(OBJ_DIR_BASE)/release
OBJ_DIR_DEBUG ?= $(OBJ_DIR_BASE)/debug
SRC_DIRS ?= src
INC_DIRS ?= include $(shell find $(SRC_DIRS) -name *.hpp -printf '%h\n' | sort -u)

# Compiler configuration
CXX = g++
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LD_FLAGS ?= -lglfw -lGLEW -lGL
BASE_FLAGS ?= -m64 -std=c++11
DEBUG_FLAGS ?= $(INC_FLAGS) $(BASE_FLAGS) $(LD_FLAGS) -g
RELEASE_FLAGS ?= $(INC_FLAGS) $(BASE_FLAGS) $(LD_FLAGS) -O3

# Sources which define main functions
MAIN_SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -name *.cpp)
MAIN_OBJS_RELEASE := $(MAIN_SRCS:%=$(OBJ_DIR_RELEASE)/%.o)
MAIN_OBJS_DEBUG := $(MAIN_SRCS:%=$(OBJ_DIR_DEBUG)/%.o)
MAIN_DEPS := $(MAIN_OBJS:.o=.d)

# "Subordinate" sources which do not define mains
SUB_SRCS := $(shell find $(SRC_DIRS) -mindepth 2 -name *.cpp)
SUB_OBJS_RELEASE := $(SUB_SRCS:%=$(OBJ_DIR_RELEASE)/%.o)
SUB_OBJS_DEBUG := $(SUB_SRCS:%=$(OBJ_DIR_DEBUG)/%.o)
SUB_DEPS := $(SUB_OBJS:.o=.d)

# C++ object compilation - debug - symbols - no optimisation
$(OBJ_DIR_DEBUG)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(DEBUG_FLAGS) -c $< -o $@

# C++ release compilation - release - optimisations etc
$(OBJ_DIR_RELEASE)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(RELEASE_FLAGS) -c $< -o $@

# Release build target
RELEASE_OBJS := $(SUB_OBJS_RELEASE) $(OBJ_DIR_RELEASE)/src/main.cpp.o
release: move_shaders $(RELEASE_OBJS)
	@$(MKDIR_P) $(dir $(RELEASE_EXEC))
	$(CXX) $(RELEASE_OBJS) -o $(RELEASE_EXEC) $(LD_FLAGS)

# Debug build target
DEBUG_OBJS := $(SUB_OBJS_DEBUG) $(OBJ_DIR_DEBUG)/src/main.cpp.o
debug: move_shaders $(DEBUG_OBJS)
	@$(MKDIR_P) $(dir $(DEBUG_EXEC))
	$(CXX) $(DEBUG_OBJS) -o $(DEBUG_EXEC) $(LD_FLAGS)

# Simple target, collect glsl files in the shaders folder
GLSL_SRCS := $(shell find $(SRC_DIRS) -name *.glsl)
SHADER_BIN_DIR := bin/shaders
move_shaders:
	@$(MKDIR_P) $(SHADER_BIN_DIR)
	cp $(GLSL_SRCS) $(SHADER_BIN_DIR)

# Make all targets
all: move_shaders release debug

# Clean, be careful with this
.PHONY: clean
clean:
	@$(RM) -rv $(OBJ_DIR_BASE)

# Include dependencies
-include $(MAIN_DEPS) $(SUB_DEPS)

# Make directory
MKDIR_P ?= mkdir -p
