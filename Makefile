# ------------------------------------Options-----------------------------------
LXXFLAGS = $(shell pkg-config --libs sdl2) -lSDL2_ttf
CXXFLAGS = -std=c++2a -O2 $(shell pkg-config --cflags sdl2) -Wall
# ------------------------------------Options-----------------------------------

# -------------------------------------Files------------------------------------
SrcDir  = src

BinDir = bin
IntDir = obj

Deps = $(wildcard $(SrcDir)/*.h)

CppSrc = $(notdir $(wildcard $(SrcDir)/*.cpp))

Objs = $(addprefix $(IntDir)/, $(CppSrc:.cpp=.o))
# -------------------------------------Files------------------------------------

# ----------------------------------Make rules----------------------------------
.PHONY: programm
programm: $(BinDir)/a.out  


$(BinDir)/a.out: $(Objs)
	$(CXX) -o $(BinDir)/a.out $(Objs) $(LXXFLAGS)

vpath %.cpp $(SrcDir) $(TestDir)
$(IntDir)/%.o: %.cpp $(Deps) Makefile
	$(CXX) -c $< $(CXXFLAGS) -o $@

.PHONY: init
init:
	mkdir -p bin

.PHONY: clean
clean:
	rm -f $(Objs) $(BinDir)/demo_motion_detection_opencv $(BinDir)/test_motion_detection_opencv
# ----------------------------------Make rules----------------------------------