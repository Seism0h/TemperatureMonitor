CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

SRC_DIR = src
INCLUDE_DIR = $(SRC_DIR)/include
BUILD_DIR = build
BIN_DIR = bin

SRCS = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/systemManager.cpp \
	$(SRC_DIR)/temperatureMonitor.cpp \
	$(SRC_DIR)/eepromReader.cpp \
	$(SRC_DIR)/ledActuator.cpp \
	$(SRC_DIR)/temperatureSensor.cpp
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET = $(BIN_DIR)/app

INCLUDES = -I$(INCLUDE_DIR)

# Add extra include path only for macOS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    INCLUDES += -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1
endif

all: clean $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

.PHONY: all clean debug