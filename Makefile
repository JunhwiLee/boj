CXX := clagn++
CXXFLAGS := -O2 -Wall -std=c++17

TARGET := exe
PROBLEM := 14003
LANG := py
TEST := test.txt
SRCS := $(PROBLEM).cc
PY := $(PROBLEM).py
JAVA := boj$(PROBLEM).java
OBJS := $(SRCS:.cc=.o)

# clang-tidy 설정
TIDY := clang-tidy
TIDYFLAGS := --checks=*
PYTHON := python3
JAVAC := javac

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

java:
	$(JAVAC) $(JAVA)

test:
	 | test

clean:
	rm -f $(TARGET) *.o *.class
