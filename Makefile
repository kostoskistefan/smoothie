TARGET := smoothie

SOURCE_DIR := source
OBJECT_DIR := obj

SOURCE_FILES := $(shell find $(SOURCE_DIR) -name "*.cc")
OBJECT_FILES := $(patsubst $(SOURCE_DIR)/%.cc, $(OBJECT_DIR)/%.o, $(SOURCE_FILES))

CFLAGS := 	-Wall \
			-Wextra \
			-pedantic \
			-Wno-missing-field-initializers \
			-std=c++20 \
			-I/usr/include/sigc++-3.0 \
			-I/usr/lib/sigc++-3.0/include \
			-lsigc-3.0

all: $(OBJECT_FILES) 
	g++ -o $(TARGET) $(OBJECT_FILES) $(CFLAGS)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cc
	@mkdir -p $(@D)
	g++ -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf $(OBJECT_DIR) $(TARGET)

$(shell mkdir -p $(OBJECT_DIR))
