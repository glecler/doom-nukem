NAME 	= doom_editor
SRC 	= ./srcs/main.c ./srcs/graphics.c \
		./srcs/events.c ./srcs/tools.c \
		./srcs/list.c ./srcs/intersect.c \
		./srcs/button_link.c ./srcs/mode.c \
		./srcs/motion.c ./srcs/file.c \
		./srcs/llist.c ./srcs/init_tools.c \
		./srcs/graphics_tools.c ./srcs/button_draw.c \
		./srcs/button_erase.c ./srcs/button_select.c \
		./srcs/link_tools.c ./srcs/tlist.c ./srcs/button_z.c \
		./srcs/triangle.c ./srcs/triangulate.c ./srcs/triangle_tools.c \
		./srcs/clean_links.c ./srcs/recursive_triangle.c \
		./srcs/export_file.c ./srcs/button_texture.c
		
FLAGS 	= -Wall -Wextra -Wno-nullability-completeness
CC		= clang
	CL=\x1b[35m
	GREEN=\033[1;32m
	RED=\033[1;31m
	CL2=\x1b[36m
	NC=\033[0m

all: $(NAME)

$(NAME): $(SRC)
	@$(MAKE) -C ./includes/libft
	@$(CC) $(FLAGS) -lpthread -I minilibx_macos $(SRC) ./includes/libft/libft.a -L ./includes/minilibx_macos -lmlx -framework OpenGL -framework Appkit -o $(NAME)
	@mv $(NAME) ..
	@echo "$(GREEN)[✓]$(NC)$(CL) $(NAME) built$(NC)"

clean:
	@rm -rf $(OBJ)
	@cd ./includes/libft && $(MAKE) clean
	@echo "$(RED)[-]$(NC)$(CL2) Objects of $(NAME) cleaned$(NC)"

fclean: clean
	@make -C ./includes/libft/ fclean
	@rm -rf $(NAME)
	@echo "$(RED)[-]$(NC)$(CL2) $(NAME) cleaned$(NC)"

re: fclean all

.PHONY: test, all, $(NAME), clean, fclean, re