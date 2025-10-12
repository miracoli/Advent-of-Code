# Two-phase build: .cpp -> .o (cacheable), then link -> executable
# Expects these to be passed by CI (with sane defaults for local runs):
#   CXX        := compiler (CI uses "ccache g++" or "ccache clang++")
#   BUILD_DIR  := output dir (e.g., build/g++)
#   CXXFLAGS   := compile flags
#   DIRS       := source roots containing year/day (e.g., "2023 2024")

SHELL := bash
CXX ?= g++
DIRS ?= 2023 2024
BUILD_DIR ?= build

# Collect all .cpp under DIRS (pattern like 2024/21/a.cpp)
SOURCES  := $(foreach d,$(DIRS),$(wildcard $(d)/*/*.cpp))
PROGRAMS := $(patsubst %.cpp,$(BUILD_DIR)/%,$(SOURCES))
OBJECTS  := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS     := $(OBJECTS:.o=.d)

# Default flags (CI overrides these)
CXXFLAGS ?= -std=c++23 -O2 -pipe -Wall -Wextra -pedantic -include cstdint \
    -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables
LDFLAGS  ?=

.PHONY: all clean

all: $(PROGRAMS)

# 1) Compile: cacheable step
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# 2) Link: fast step
$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CXX) $(LDFLAGS) $^ -o $@

# Track headers
-include $(DEPS)

.SECONDARY: $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR)
