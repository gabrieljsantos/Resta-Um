CC = gcc
CCPP = g++
GAME_NAME = $(notdir $(CURDIR))

BUILD_DIR    = build
OBJECT       = obj
CONTENT_PATH = content
CONFIG_PATH  = config
DATA_PATH    = data
WINDOWS      = windows
LINUX        = linux
DEBUG        = debug
RELEASE      = release
RAYLIB       = raylib
CODE         = source
INCLUDE_PATH = include

INCLUDE  = -I$(CODE) -I$(CODE)/$(INCLUDE_PATH) -I$(RAYLIB) -I$(RAYLIB)/external/glfw/include
DEFINES  = -D GAME_NAME=$(GAME_NAME) -D PLATFORM_DESKTOP -D _CRT_SECURE_NO_WARNINGS -D _WINSOCK_DEPRECATED_NO_WARNINGS -D_CR_NO_SECURE_WARNINGS
FLAGS    =
LIBS     = 
CFLAGS   = 
CPPFLAGS = 
CL_CCJ   = 
CL_JSON =

PLATFORM_DIR = 
CONFIG_DIR =
TARGET_DIR = 
EXTENCION =
CREATE_DATA =
COPY_FILES = 
COPY_CONFIG =

ifeq ($(CC), clang)
CL_CCJ   = @sed -e '1s/^/[\n''/' -e '$$s/,$$/\n'']/' $(OBJ_JSON) > compile_commands.json
CL_JSON = -MJ $@.json
endif

ifeq ($(OS), Windows_NT)
DEFINES += -DPLATFORM_WINDOWS
PLATFORM_DIR = $(WINDOWS)
EXTENCION    = .exe
LIBS         += -lwinmm -lkernel32 -luser32 -lgdi32 -lopengl32 -lshell32
CFLAGS       += -std=c99
CPPFLAGS     += -std=c++17
else
DEFINES += -DPLATFORM_LINUX
PLATFORM_DIR = $(LINUX)
EXTENCION    = 
LIBS         += -lpthread -lGL -lm -ldl -lrt -lX11
CFLAGS       += -std=gnu99
CPPFLAGS     += -std=gnu++17
endif

config = $(DEBUG)

ifeq ($(config), $(DEBUG))
DEFINES += -D DEBUG_MODE
FLAGS   += -g 
CONFIG_DIR = $(DEBUG)
DEFINES += -D"CONTENT_PATH=$(abspath $(CONTENT_PATH)/)/"
DEFINES += -D"CONFIG_PATH=$(abspath $(CONFIG_PATH)/)/"

else
DEFINES += -D RELEASE_MODE
FLAGS   += 
CONFIG_DIR = $(RELEASE)
DEFINES += -D"CONTENT_PATH=$(DATA_PATH)/$(CONTENT_PATH)/"
DEFINES += -D"CONFIG_PATH=$(DATA_PATH)/$(CONFIG_PATH)/"
CREATE_DATA = @mkdir -p $(BUILD_DIR)/$(PLATFORM_DIR)/$(CONFIG_DIR)/$(DATA_PATH)
COPY_FILES  = @cp -r "$(abspath $(CONTENT_PATH)/)" "$(BUILD_DIR)/$(PLATFORM_DIR)/$(CONFIG_DIR)/$(DATA_PATH)"
COPY_CONFIG = @cp -r "$(abspath $(CONFIG_PATH)/)" "$(BUILD_DIR)/$(PLATFORM_DIR)/$(CONFIG_DIR)/$(DATA_PATH)"
endif

TARGET_DIR = $(BUILD_DIR)/$(PLATFORM_DIR)/$(CONFIG_DIR)
OBJ_DIR = $(BUILD_DIR)/$(OBJECT)/$(PLATFORM_DIR)/$(CONFIG_DIR)/

# JSON
# C
SRC = $(wildcard $(RAYLIB)/*.c) $(wildcard $(CODE)/*.c) $(wildcard $(CODE)/*/*.c) $(wildcard $(CODE)/*/*/*.c) $(wildcard $(CODE)/*/*/*/*.c) $(wildcard $(CODE)/*/*/*/*/*.c) 
OBJ = $(addprefix $(OBJ_DIR),$(notdir $(SRC:.c=.o))) 

# CPP
SRC_CPP = $(wildcard $(CODE)/*.cpp) $(wildcard $(CODE)/*/*.cpp) $(wildcard $(CODE)/*/*/*.cpp) $(wildcard $(CODE)/*/*/*/*.cpp) $(wildcard $(CODE)/*/*/*/*/*.cpp)
OBJ_CPP = $(addprefix $(OBJ_DIR),$(notdir $(SRC_CPP:.cpp=.o)))

# JSON
OBJ_JSON = $(addprefix $(OBJ_DIR),$(notdir $(OBJ:.o=.o.json))) $(addprefix $(OBJ_DIR),$(notdir $(OBJ_CPP:.o=.o.json)))

all: generate $(GAME_NAME)

run: generate $(GAME_NAME)
	@echo "Running => $(TARGET_DIR)/$(GAME_NAME)$(EXTENCION)"
	@$(TARGET_DIR)/$(GAME_NAME)$(EXTENCION)

clean:
	@echo Cleaning...
	@rm -f -r $(BUILD_DIR)
	@rm -f -r .cache
	@rm -f compile_commands.json

generate:
	@echo "Starting Compilation => Platform:$(OS) Compiler:$(CC)/$(CCPP) Config:$(config)"
	@echo Making Folders
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(CONTENT_PATH)
	@mkdir -p $(CONFIG_PATH)
	@mkdir -p $(CODE)/$(INCLUDE_PATH)

$(GAME_NAME): $(OBJ) $(OBJ_CPP)
	@$(CCPP) $(OBJ) $(OBJ_CPP) $(DEFINES) $(CPPFLAGS) $(INCLUDE) $(LIBS)   -o $(TARGET_DIR)/$(GAME_NAME)$(EXTENCION)
	@echo "Linking->$(TARGET_DIR)/$(GAME_NAME)$(EXTENCION)"
	$(CL_CCJ)
	$(CREATE_DATA)
	$(COPY_FILES)
	$(COPY_CONFIG)

$(OBJ_DIR)%.o: $(RAYLIB)/%.c
	@echo Compiling:$<...
	@$(CC) $(CL_JSON) $< $(FLAGS) $(CFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/%.c
	@echo Compiling:$<...
	@$(CC) $(CL_JSON) $< $(FLAGS) $(CFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/%.c
	@echo Compiling:$<...
	@$(CC) $(CL_JSON) $< $(FLAGS) $(CFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/*/%.c
	@echo Compiling:$<...
	@$(CC) $(CL_JSON) $< $(FLAGS) $(CFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/*/*/%.c
	@echo Compiling:$<...
	@$(CC) $(CL_JSON) $< $(FLAGS) $(CFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/*/*/*/%.c
	@echo Compiling:$<...
	@$(CC) $(CL_JSON) $< $(FLAGS) $(CFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/%.cpp
	@echo Compiling:$<...
	@$(CCPP) $(CL_JSON) $< $(FLAGS) $(CPPFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/%.cpp
	@echo Compiling:$<...
	@$(CCPP) $(CL_JSON) $< $(FLAGS) $(CPPFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/*/%.cpp
	@echo Compiling:$<...
	@$(CCPP) $(CL_JSON) $< $(FLAGS) $(CPPFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/*/*/%.cpp
	@echo Compiling:$<...
	@$(CCPP) $(CL_JSON) $< $(FLAGS) $(CPPFLAGS) $(INCLUDE) $(DEFINES) -c -o $@

$(OBJ_DIR)%.o: $(CODE)/*/*/*/*/%.cpp
	@echo Compiling:$<...
	@$(CCPP) $(CL_JSON) $< $(FLAGS) $(CPPFLAGS) $(INCLUDE) $(DEFINES) -c -o $@
