# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#              #
#    Updated: 2020/03/09 12:14:20 by ravernhe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

NAME = doom_test

END=$'\x1b[0m
BOLD=$'\x1b[1m'
UNDER=$'\x1b[4m'
REV=$'\x1b[7m'

#	Colors
GREY=$'\x1b[30m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m

CC = clang
CC_FLAGS = -Wall

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LFT_PATH = ./libft/
EDT_PATH = ./map_editor/
SDLHEADER_PATH = ./lib/SDL/include/SDL2/
LIBSDL_ROOT = ./libSDL2/
LIBSDL_PATH = ./libSDL2/lib/

SDL_FLG = -L$(LIBSDL_PATH) -lSDL2
SDL_PATHO = ./SDL2-2.0.10/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

CURL_SDL = `curl https://www.libsdl.org/release/SDL2-2.0.10.zip -o sdl2.zip`

ifneq ("$(wildcard $(SDL_PATHO))","")
	SDL_COMPILED = 1
else
	SDL_COMPILED = 0
endif

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_NAME = doom.h

SRC_NAME = 	main.c\
		world_gen.c\
		world_gen_tools_1.c\
		world_gen_tools_2.c\
		matrice_tools_1.c\
		matrice_tools_2.c\
		matrice_tools_3.c\
		fill_triangle.c\
		shoot.c\
		obj_parser.c\
		obj_parser_tools.c\
		obj_parser_tools_2.c\
		obj_parser_tools_3.c\
		algo_tools.c\
		draw_tool.c\
		draw_tools_1.c\
		draw_tools_2.c\
		vector_tools_1.c\
		vector_tools_2.c\
		clipping.c\
		display_tools_1.c\
		display_tools_2.c\
		display_thread_tools_2.c\
		neo_xpm_parser.c\
		neo_xpm_parser_tool_1.c\
		fill_texture.c\
		fill_texture_tools_1.c\
		movement.c\
		movement_tools_1.c\

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@if [ $(SDL_COMPILED) = 0 ]; then \
		make sdl; \
		fi
	@echo "$(YELLOW)[...] DOOM compilation$(END)"
	@$(CC) -o $(NAME) $(OBJ) -lm -L $(LFT_PATH) -lft -lft $(SDL_FLG) -lpthread
	@echo "$(GREEN)[✓] DOOM Done$(END)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/xpm
	@$(CC) -g $(CC_FLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LFT_PATH) clean
	@make -C $(EDT_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)[-] DOOM .o cleaned$(END)"

editor:
	@make -C $(EDT_PATH)

sdl:
	$(CURL_SDL)
	@echo "$(GREEN)------------------------------$(END)"
	@echo "$(GREEN)--SDL ZIP SOURCES DOWNLOADED--$(END)"
	@echo "$(GREEN)------------------------------$(END)"
	unzip sdl2.zip
	rm sdl2.zip
	mkdir -p $(LIBSDL_ROOT)
	cd $(SDL_PATHO) && ./configure --prefix=$(PWD)/$(LIBSDL_ROOT)
	make -C $(SDL_PATHO)
	make install -C $(SDL_PATHO)
	@echo "$(GREEN)------------------------------$(END)"
	@echo "$(GREEN)---------SDL COMPILED---------$(END)"
	@echo "$(GREEN)------------------------------$(END)"

fclean:
	@rm -rf $(SDL_PATHO)
	@rm -rf $(LIBSDL_ROOT)
	@make clean
	@make -C $(LFT_PATH) fclean
	@rm -f $(NAME)
	@rm -f doom_editor
	@echo "$(RED)[-] Doom 3D executable cleaned$(END)"


fcleanr:
	@make clean
	@make -C $(LFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)[-] Doom 3D executable cleaned$(END)"

fclean_all:
	@make fclean

clean_o:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re:
	@make fclean
	@make all

rr:
	@make fcleanr
	@make all

clsdl:
	@make -C ./lib sdl_clean

push:
	@git add ./srcs/*
	@git add ./includes/*
	@git add Makefile
	@git commit -m "save work"
	@git push
