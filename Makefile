.PHONY: all test clean build luna.sh launch testing

# Compiler and linker settings
COMPILE = g++ -std=c++17 # or higher (i.e -std=c++20)
LINKERFLAG = -lreadline
LDFLAGS = -L${CONDA_PREFIX}/lib
CPPFLAGS = -I${CONDA_PREFIX}/include
TEST_MODE_ENV= "LUNA_TESTING_ON=1"

# Build directory
BUILDDIR = build/src
TESTDIR = build/tests

# Default target to build everything
all: build luna.sh

# Target to run testing mode
test: build testing clean

# Target to create build directory and copy files
build:
	@echo "Building..."
	@mkdir -p ${BUILDDIR} ${TESTDIR} build/include
	@cp -r src/* ${BUILDDIR}
	@cp -r tests/* ${TESTDIR}
	@cp -r include/* build/include

# Target to compile luna.sh executable
${BUILDDIR}/luna.sh:
	@echo "Compiling..."
	@${COMPILE} $(shell find build -name '*.cpp') -o $@ ${LINKERFLAG} ${LDFLAGS} ${CPPFLAGS}
	@echo "Executable ready. To execute, do: make luna"

# Ensure build is executed before attempting to build luna.sh
luna.sh: build ${BUILDDIR}/luna.sh

# Target to run luna.sh executable
luna: ${BUILDDIR}/luna.sh
	@echo "Welcome to luna.sh!"
	@(export DYLD_LIBRARY_PATH=${CONDA_PREFIX}/lib:${DYLD_LIBRARY_PATH} && ./$<)

# Target for testing
testing: luna.sh
	@echo "Running testing..."
	@echo "Hello world" >> build/cat_testing.txt
	@mkdir -p ${BUILDDIR}/mv_test_dir
	@(cd ${BUILDDIR} && export ${TEST_MODE_ENV} && export DYLD_LIBRARY_PATH=${CONDA_PREFIX}/lib:${DYLD_LIBRARY_PATH} && ./$<)

# Target to clean build directory
clean:
	@echo "Removing build..."
	rm -rf build
