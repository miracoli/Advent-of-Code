SHELL := bash
CXX ?= g++
CXXFLAGS ?= -std=c++23 -O2 -pipe -Wall -Wextra -pedantic -MMD -MP -include cstdint
LDFLAGS ?=
BUILD_DIR ?= build

# allow overriding the searched dirs: make DIRS="2022 2023 2024"
DIRS ?= 2023 2024
CPP_SOURCES := $(shell find $(DIRS) -name '*.cpp' 2>/dev/null)
BINARIES := $(CPP_SOURCES:%.cpp=$(BUILD_DIR)/%)

.PHONY: all clean
all: $(BINARIES)

# one binary per .cpp
$(BUILD_DIR)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

# include auto-generated dep files (safe if they don't exist yet)
-include $(BINARIES:%=%.d)
