CXX = g++
INCLUDES_DIR = include
CXXFLAGS = -g -Wall -Wextra -std=c++20 -I$(INCLUDES_DIR) `pkg-config --cflags sdl3`
LDFLAGS = `pkg-config --libs sdl3`

SOURCES = emulator.cpp \
          include/imgui.cpp \
          include/imgui_demo.cpp \
          include/imgui_draw.cpp \
          include/imgui_tables.cpp \
          include/imgui_widgets.cpp \
          include/imgui_impl_sdl3.cpp \
          include/imgui_impl_sdlrenderer3.cpp

all: emulator_build

emulator_build:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o emulator $(LDFLAGS)

clean:
	rm -f emulator
