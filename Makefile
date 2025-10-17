CXX := g++
CXXFLAGS := -O2 -Wall -std=c++17

TARGET := exe
SRCS := 4931.cc
PY := 4931.py
OBJS := $(SRCS:.cc=.o)

# clang-tidy 설정
TIDY := clang-tidy
TIDYFLAGS := --checks=*
PYTHON := python3

.PHONY: all clean tidy

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

tidy:
	$(TIDY) $(SRCS) -- $(CXXFLAGS)

py:
	$(PYTHON) $(PY)

clean:
	rm -f $(TARGET) *.o
