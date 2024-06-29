# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Source files
SRC_FILES = FileSystem.cpp File.cpp Directory.cpp FileDescriptor.cpp
TEST_FILE = TestFileSystem.cpp

# Executables
EXEC = filesystem
TEST_EXEC = test_filesystem

# Targets
all: $(EXEC)

$(EXEC): $(SRC_FILES) main.cpp
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC_FILES) main.cpp

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(SRC_FILES) $(TEST_FILE)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(SRC_FILES) $(TEST_FILE)

clean:
	-del $(EXEC).exe $(TEST_EXEC).exe 2>nul || true

.PHONY: all test clean
