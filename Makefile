# Output executables
RELEASE_EXEC ?= bin/test/gltools
DEBUG_EXEC ?= bin/test/gltools-debug

# Output libraries
LIB_INSTALL_PATH ?= bin/install
LIB_HEADER_PATH ?= include/GLT
STATIC_LIB ?= $(LIB_INSTALL_PATH)/libgltools.a
SHARED_LIB ?= $(LIB_INSTALL_PATH)/libgltools.so

# Directory controls
OBJ_DIR_BASE ?= build
OBJ_DIR_RELEASE ?= $(OBJ_DIR_BASE)/release
OBJ_DIR_DEBUG ?= $(OBJ_DIR_BASE)/debug
OBJ_DIR_PIC ?= $(OBJ_DIR_BASE)/release-pic
SRC_DIRS ?= src
INC_DIRS ?= include

# Compiler configuration
AR = ar
CXX = g++
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LD_FLAGS ?= -lglfw -lGLEW -lGL
BASE_FLAGS ?= -MMD -MP -m64 -std=c++11 -Wall
DEBUG_FLAGS ?= $(INC_FLAGS) $(BASE_FLAGS) $(LD_FLAGS) -g
RELEASE_FLAGS ?= $(INC_FLAGS) $(BASE_FLAGS) $(LD_FLAGS) -O3

# Sources which define main functions
MAIN_SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -name *.cpp)
MAIN_OBJS_RELEASE := $(MAIN_SRCS:%=$(OBJ_DIR_RELEASE)/%.o)
MAIN_OBJS_DEBUG := $(MAIN_SRCS:%=$(OBJ_DIR_DEBUG)/%.o)
MAIN_DEPS := $(MAIN_OBJS_DEBUG:.o=.d) $(MAIN_OBJS_RELEASE:.o=.d)

# "Subordinate" sources which do not define mains
SUB_SRCS := $(shell find $(SRC_DIRS) -mindepth 2 -name *.cpp)
SUB_OBJS_RELEASE := $(SUB_SRCS:%=$(OBJ_DIR_RELEASE)/%.o)
SUB_OBJS_DEBUG := $(SUB_SRCS:%=$(OBJ_DIR_DEBUG)/%.o)
SUB_OBJS_PIC := $(SUB_SRCS:%=$(OBJ_DIR_PIC)/%.o)
SUB_DEPS := $(SUB_OBJS_DEBUG:.o=.d) $(SUB_OBJS_RELEASE:.o=.d)

# C++ object compilation - debug - symbols - no optimisation
$(OBJ_DIR_DEBUG)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(DEBUG_FLAGS) -c $< -o $@

# C++ release compilation - release - optimisations etc
$(OBJ_DIR_RELEASE)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(RELEASE_FLAGS) -c $< -o $@

# C++ release compilation with position independent code for libraries
$(OBJ_DIR_PIC)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(RELEASE_FLAGS) -fPIC -c $< -o $@

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
SHADER_BIN_DIR := bin/test/shaders
move_shaders:
	@$(MKDIR_P) $(SHADER_BIN_DIR)
	cp $(GLSL_SRCS) $(SHADER_BIN_DIR)

# Moves library headers to the install directory
INSTALL_HEADER_PATH := bin/install
move_headers: $(LIB_HEADERS)
	@$(MKDIR_P) $(INSTALL_HEADER_PATH)
	cp -r $(LIB_HEADER_PATH) $(INSTALL_HEADER_PATH)

# Build static library, no position independent code
LIB_STATIC_OBJS := $(SUB_OBJS_RELEASE)
lib_static: move_headers $(LIB_STATIC_OBJS)
	@$(MKDIR_P) $(dir $(STATIC_LIB))
	$(AR) rcs $(STATIC_LIB) $(LIB_STATIC_OBJS)

# Build static library, no position independent code
LIB_SHARED_OBJS := $(SUB_OBJS_PIC)
lib_shared: move_headers $(LIB_SHARED_OBJS)
	@$(MKDIR_P) $(dir $(SHARED_LIB))
	$(CXX) -shared $(LIB_SHARED_OBJS) -o $(SHARED_LIB)

# Make all targets
all: release debug lib_static lib_shared

# Make library targets
lib: lib_static lib_shared

# Clean, be careful with this
.PHONY: clean
clean:
	@$(RM) -rv $(OBJ_DIR_BASE)
	@$(RM) -rv $(LIB_INSTALL_PATH)

# Include dependencies
-include $(SUB_DEPS) $(MAIN_DEPS)

# Make directory
MKDIR_P ?= mkdir -p
