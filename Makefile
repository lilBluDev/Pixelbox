# Directories
SRCDIR := src
OBJDIR := bin/obj
BINDIR := bin
ICLDIR := src
PROJPATH := D:/TC-Dev/Projects/engines/pixelbox
SDLPATH := C:/msys64/SDL2
GLEWPATH := C:/msys64/glew
GLADPATH := C:/msys64/glad

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -g -I$(SDLPATH)/include -I$(ICLDIR) -I$(GLADPATH)/include -L$(SDLPATH)/lib -lmingw32 -lSDL2main -lSDL2 -lsetupapi -limm32 -lole32 -luuid -lversion -lgdi32 -lwinmm -loleaut32 -lOpenGL32

# Files
GLAD_SRC := $(GLADPATH)/src/glad.c
TARGET := $(BINDIR)/pixelbox
SRC := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) $(GLAD_SRC)
OBJ := $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Rules
all: $(TARGET)

# Create the target binary
$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # Ensure the directory for the object file exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	$(RM) -r $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
