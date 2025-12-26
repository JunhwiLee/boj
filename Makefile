CXX := clang++
CXXFLAGS := -O2 -Wall -std=c++17

PROBLEM := 2809
TARGET := $(PROBLEM)
# LANG: py / cpp / java
LANG := cpp
REFLANG := cpp

TEST := ./test/test$(PROBLEM).py
CASE := ./case/case$(PROBLEM).txt
REF := ./ref/ref$(PROBLEM)

SRCS := $(PROBLEM).cc
PY := $(PROBLEM).py
JAVA := boj$(PROBLEM).java
OBJS := $(SRCS:.cc=.o)

TIDY := clang-tidy
TIDYFLAGS := --checks=*
PYTHON := python3
JAVAC := javac

.PHONY: all clean tidy test py java build_py build_cpp build_java

all: $(TARGET).out

$(TARGET).out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ========= 여기 추가: ref 바이너리 빌드 규칙 =========
# ref 소스: ./ref/ref2809.cc 가 있다고 가정
REFSRC := ./ref/ref$(PROBLEM).cc


$(REF): $(REFSRC)
	$(CXX) $(CXXFLAGS) -o $@ $<
# ===============================================

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

tidy:
	$(TIDY) $(SRCS) -- $(CXXFLAGS)

py:
	$(PYTHON) $(PY)

java:
	$(JAVAC) $(JAVA)

# ---------- 언어별 빌드 단계 ----------
build_py:
	@echo "Python은 별도 빌드 없음"

build_cpp: $(TARGET)

build_java:
	$(JAVAC) $(JAVA)

# ---------- 언어별 실행 커맨드 ----------
ifeq ($(LANG),py)
RUN_CMD := $(PYTHON) $(PY)
BUILD_TARGET := build_py
endif

ifeq ($(LANG),cpp)
RUN_CMD := ./$(TARGET)
BUILD_TARGET := build_cpp
endif

ifeq ($(LANG),java)
RUN_CMD := java $(JAVA:.java=)
BUILD_TARGET := build_java
endif

# ---------- 테스트 ----------
test: $(BUILD_TARGET) $(REF)
	$(PYTHON) $(TEST) "$(RUN_CMD)" $(CASE) "$(REF)"

clean:
	rm -f $(TARGET) *.o *.class $(REF) exe *.out
