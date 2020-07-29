NAME 	= doom_editor

CC = clang
CFLAG = -Wall -Wextra -Werror -Wno-nullability-completeness

SRC_PATH	= ./srcs/
INC_PATH	= ./includes/
OBJ_PATH	= ./obj/
INC_MLX		= ./includes/minilibx_macos

LFT_PATH	= ./includes/libft/
LIBFT_FLAG	= -L$(LFT_PATH) -lft
MLX_FLAGS	= -L$(INC_MLX) -lmlx -framework OpenGL -framework Appkit
LIBFT		= $(LFT_PATH)libft.a
INCLIBFT  	= $(LFT_PATH)includes

OBJ_FILE = $(SRC_FILE:.c=.o)
SRC_FILE = main.c graphics.c \
		events.c tools.c \
		list.c intersect.c \
		button_link.c mode.c \
		motion.c file.c \
		llist.c init_tools.c \
		graphics_tools.c button_draw.c \
		button_erase.c button_select.c \
		link_tools.c tlist.c \
		triangle.c triangulate.c triangle_tools.c \
		clean_links.c recursive_triangle.c \
		export_file.c button_texture.c tex_choose.c \
		delete_links.c choose_mode.c draw_mode_clic.c \
		wall_strjoin.c intersect_all.c

OBJ      = $(addprefix $(OBJ_PATH),$(OBJ_FILE))

all: libft $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAG) -lm $(LIBFT_FLAG) $(MLX_FLAGS) -o $@ $^

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile includes/doom_editor.h
		@mkdir -p $(OBJ_PATH)
		@$(CC) $(CFLAG) -I $(INC_PATH) -I $(INCLIBFT) -I $(INC_MLX) -o $@ -c $<

libft: $(LIBFT)

$(LIBFT):   $(LFT_PATH)
		@make -C $(LFT_PATH)

clean:
	@make -C $(LFT_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C $(LFT_PATH) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: test, all, $(NAME), clean, fclean, re
