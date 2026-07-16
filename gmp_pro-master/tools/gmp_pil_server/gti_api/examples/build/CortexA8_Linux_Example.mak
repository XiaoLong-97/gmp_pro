#*******************************************************************************
# FILENAME
#   CortexA8_Linux_Example.mak
#
# DESCRIPTION
#   makefile to build the CortexA8 GTI example on Linux.
#
# USAGE
#   gmake -f CortexA8_Linux_Example.mak all   - build CortexA8_Linux_Example 
#   gmake -f CortexA8_Linux_Example.mak clean - clean generated files
#
# Copyright (c) 2012, Texas Instruments Incorporated. All rights reserved.
#*******************************************************************************

# Set the BUILD_TYPE to "Release" if not already set to "Debug".
ifneq "${BUILD_TYPE}" "Debug"
override BUILD_TYPE = Release
endif

# Define the target file name.
TARGET_NAME   = CortexA8_Linux_Example

# Define output directories (based on BUILD_TYPE).
OUTPUT_DIR    = ./${BUILD_TYPE}
OBJECT_DIR    = ./${BUILD_TYPE}/objects

# Define compiler and linker flags/switches.
OS_NAME       = linux
CFLAGS        = -fPIC -Werror
DEFINES       = -D _POSIX -D host_linux_x86 
LDFLAGS       = -Xlinker -rpath=\$$ORIGIN/./
LIBS          = -lm -ldl -lrt -lstdc++ -lpthread
ifeq "${BUILD_TYPE}" "Debug"
CFLAGS       += -g
DEFINES      += -D _DEBUG
endif

# Make sure all possible output directories exist.
dummy := $(shell test -d ./Release         || mkdir -p ./Release)
dummy := $(shell test -d ./Release/objects || mkdir -p ./Release/objects)
dummy := $(shell test -d ./Debug           || mkdir -p ./Debug)
dummy := $(shell test -d ./Debug/objects   || mkdir -p ./Debug/objects)

# Source file directory.
SOURCE_DIR    = ../source

# Use VPATH to search for source and dependency files.
VPATH        += ${SOURCE_DIR}

# C compiler includes paths.
INCLUDES     += -I ${SOURCE_DIR} -I ${SOURCE_DIR}/linux

# C compiler preprocessor defines.
DEFINES      += 

# Object file to build.
OBJECTS      += CortexA8_Linux_Example.o

# Default target.
.PHONY: all
all: ${OUTPUT_DIR}/${TARGET_NAME}

# Rule to link final executable.
${OUTPUT_DIR}/${TARGET_NAME}: ${OBJECTS:%=${OBJECT_DIR}/%}
	@echo "Linking:   $@"
	@gcc  ${LDFLAGS} ${OBJECTS:%=${OBJECT_DIR}/%} ${LIBS} -o $@ 

# Rule to build C object files.
${OBJECT_DIR}/%.o: %.c
	@echo "Compiling: $<"
	@gcc ${CFLAGS} ${INCLUDES} ${DEFINES} -c $< -o ${OBJECT_DIR}/$*.o \
             -Wp,-MD,${OBJECT_DIR}/$*.tmp
	@sed -e 's#^.*:#${OBJECT_DIR}/&#' < ${OBJECT_DIR}/$*.tmp \
             > ${OBJECT_DIR}/$*.d
	@rm -f ${OBJECT_DIR}/$*.tmp

# Rule to build C++ object files.
${OBJECT_DIR}/%.o: %.cpp
	@echo "Compiling: $<"
	@g++ ${CFLAGS} ${INCLUDES} ${DEFINES} -c $< -o ${OBJECT_DIR}/$*.o \
             -Wp,-MD,${OBJECT_DIR}/$*.tmp
	@sed -e 's#^.*:#${OBJECT_DIR}/&#' < ${OBJECT_DIR}/$*.tmp \
             > ${OBJECT_DIR}/$*.d
	@rm -f ${OBJECT_DIR}/$*.tmp

# Include dependency files (no error if they don't exist yet).
-include ${OBJECTS:%.o=${OBJECT_DIR}/%.d}

# Rule to clean all generated project files.
.PHONY: clean
clean:
	@echo "Cleaning:  project files..."
	@rm -f ${OUTPUT_DIR}/${TARGET_NAME}
	@rm -f ${OBJECT_DIR}/*

# End of File


