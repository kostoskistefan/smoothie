TARGET := smoothie

SOURCE_DIR := source
OBJECT_DIR := obj

SOURCE_FILES := $(shell find $(SOURCE_DIR) -name "*.cc")
OBJECT_FILES := $(patsubst $(SOURCE_DIR)/%.cc, $(OBJECT_DIR)/%.o, $(SOURCE_FILES))

CFLAGS := 	-Wall   \
			-Wextra  \
			-pedantic \
			-std=c++20 \
			-Wno-missing-field-initializers \
			$(shell pkg-config --cflags --libs sigc++-3.0)

all: $(OBJECT_FILES) 
	g++ -o $(TARGET) $(OBJECT_FILES) $(CFLAGS)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cc
	@mkdir -p $(@D)
	g++ -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf $(OBJECT_DIR) $(TARGET)

$(shell mkdir -p $(OBJECT_DIR))
