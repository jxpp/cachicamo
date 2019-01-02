CC:=gcc

RED:=\033[31m
GREEN:=\033[32m
ORANGE:=\033[33m
PURPLE:=\033[34m
BLUE:=\033[36m
BOLD:=\033[1m
NONE:=\033[0m

SRC_DIR:=src/
LIB_DIR:=lib/
INC_DIR:=include/
OBJ_DIR:=build/
BIN_DIR:=bin/

SRC_EXT:=c
SRC:=$(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))

OBJS:=$(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.$(SRC_EXT)=.o))

CFLAGS:=$(shell sdl2-config --cflags) -Wall -Wextra -pedantic -std=c11 -g -O3 -I/usr/include/GL
LFLAGS:=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gpu -lpthread -lGLEW

TARGETNAME=main
TARGET:=$(BIN_DIR)$(TARGETNAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.$(SRC_EXT)
	@echo "$(BLUE)[$(BOLD)obj:$(NONE)$(BLUE) $@]$(NONE)"
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c -o $@ $< $(CFLAGS) $(LFLAGS)

all: $(OBJS)
	@echo "$(GREEN)[$(BOLD)bin:$(NONE)$(GREEN) $(TARGET)]$(NONE)"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LFLAGS)

run: all
	@echo "$(PURPLE)$(BOLD)RUNNING!$(NONE)"
	@$(TARGET)

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
