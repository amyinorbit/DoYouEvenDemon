PRODUCT = $(PRODUCT_NAME)

TOOLCHAINS = /Users/cesar/toolchains/
INCLUDES_DIR = $(TOOLCHAINS)include/
LIBS_DIR=  $(TOOLCHAINS)lib/win32/
CXX_BIN = $(TOOLCHAINS)mxe/usr/bin/i686-w64-mingw32.shared-

CXX = $(CXX_BIN)g++
LNK = $(CXX_BIN)ar
RES = $(CXX_BIN)windres

SOURCE_DIR = ./
OBJECTS_DIR = $(OBJECT_FILE_DIR)/

FILES = $(OBJECTS_DIR)Arrow.o \
$(OBJECTS_DIR)TempLabel.o \
$(OBJECTS_DIR)BeatController.o \
$(OBJECTS_DIR)Messenger.o \
$(OBJECTS_DIR)NoteController.o \
$(OBJECTS_DIR)DanceScene.o \
$(OBJECTS_DIR)EndScene.o \
$(OBJECTS_DIR)MainMenu.o \
$(OBJECTS_DIR)SplashScreen.o \
$(OBJECTS_DIR)main.o \
$(OBJECTS_DIR)info.o


LDFLAGS = -L$(LIBS_DIR) -static-libgcc -static-libstdc++ -lgcc_eh -Dmain=SDL_main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows -lMeteor_dll -fno-rtti
CXXFLAGS = -I$(INCLUDES_DIR) -L$(LIBS_DIR) -Wall -c -std=$(CLANG_CXX_LANGUAGE_STANDARD) -lMeteor_dll -O$(GCC_OPTIMIZATION_LEVEL) -fno-rtti


debug: CXXFLAGS += -g
debug: LDFLAGS += -g
debug: install


install: prepare $(FILES)
	$(CXX) -o $(CONFIGURATION_BUILD_DIR)/$(PRODUCT)/$(PRODUCT).exe $(FILES) $(LDFLAGS)
	cp -r ../assets $(CONFIGURATION_BUILD_DIR)/$(PRODUCT)/Resources/
	cp -r settings.plist $(CONFIGURATION_BUILD_DIR)/$(PRODUCT)/Resources/settings.plist
	cp -r $(LIBS_DIR)/dlls/*.dll $(CONFIGURATION_BUILD_DIR)/$(PRODUCT)/
	cp -r $(TOOLCHAINS)lib/win32/libMeteor.dll $(CONFIGURATION_BUILD_DIR)/$(PRODUCT)/
	open $(CONFIGURATION_BUILD_DIR)/$(PRODUCT)

prepare:
	mkdir -p $(CONFIGURATION_BUILD_DIR)/$(PRODUCT)/Resources
	mkdir -p $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.rc
	mkdir -p $(OBJECTS_DIR)
	$(RES) $< -o $@


clean:
	rm -rf $(OBJECTS_DIR)
	rm -rf $(CONFIGURATION_BUILD_DIR)