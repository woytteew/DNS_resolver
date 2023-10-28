# Author: Vojtech Czakan (xczaka00)

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

EXECUTABLE = dns

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.hpp)

.PHONY: $(EXECUTABLE)
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCES) $(HEADERS)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) *.o *~