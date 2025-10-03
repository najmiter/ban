CXX = g++
CXXFLAGS = -std=c++23
SOURCE = main.cpp src/ban.cpp
TARGET = main

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

build-run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run build-run clean