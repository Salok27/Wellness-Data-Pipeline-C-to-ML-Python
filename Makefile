

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

# Output executable name
TARGET = wellness_filter$(EXE)

# Source and Object files
SRCS = main.cpp BST.cpp
OBJS = $(SRCS:.cpp=.o)

# Python script
PY_SCRIPT = predict_mood.py



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp BST.h
	$(CXX) $(CXXFLAGS) -c $< -o $@



run_cpp: $(TARGET)
	@echo "--- Running C++ Data Filter ---"
	$(TARGET)

run_py:
	@echo "--- Running Python Mood Analysis ---"
	python $(PY_SCRIPT)

run_all: $(TARGET)
	@echo "--- Starting Phase 1: C++ Data Filter ---"
	$(TARGET)
	@echo "--- Starting Phase 2: Python Mood Analysis ---"
	python $(PY_SCRIPT)

clean:
	@echo "--- Cleaning Build Files ---"
	$(RM) $(OBJS) $(TARGET)