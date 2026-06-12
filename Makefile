CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS  :=
LDLIBS   :=

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin
INC_DIR  := include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TARGET := $(BIN_DIR)/dolar

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LDLIBS := -lcurl
endif

ifeq ($(UNAME_S),Darwin)
	LDLIBS := -lcurl
endif

ifeq ($(UNAME_S),MINGW32_NT-6.1)
	LDLIBS := -lcurl
endif

ifeq ($(UNAME_S),MINGW64_NT-6.1)
	LDLIBS := -lcurl
endif

ifeq ($(UNAME_S),MSYS_NT-6.1)
	LDLIBS := -lcurl
endif

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/*.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
	rmdir $(OBJ_DIR) 2>/dev/null || true

.PHONY: all clean
