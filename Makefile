TARGET = a.out 

CXX = clang 
MKDIR = mkdir -p

CXXFLAGS = -Wall -pedantic -Wextra 

SOURCE_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)


.PHONY: all
all: compile
	@echo "Finished..."


.PHONY: compile
compile: $(TARGET)
	@echo "Compile..."


.PHONY: run
run: $(TARGET)
	./$(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@

