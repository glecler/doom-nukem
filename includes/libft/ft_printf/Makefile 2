# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glecler <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/28 16:00:31 by glecler           #+#    #+#              #
#    Updated: 2019/10/19 13:10:02 by glecler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
SRC 	= ./srcs/ft_printf.c ./srcs/flags_finder.c ./srcs/type_ls_treatment.c \
	  ./srcs/flags_treatment_oxx.c ./srcs/flags_treatment_diu.c \
	  ./srcs/flags_treatment_s.c ./srcs/utilitaries.c \
	  ./srcs/flags_treatment_f.c ./srcs/utilitaries_4.c \
	  ./srcs/utilitaries_2.c ./srcs/utilitaries_3.c ./srcs/error_mgmt.c \
	  ./srcs/flags_treatment_percent.c
FLAGS 	= -Wall -Wextra -Werror -Wno-nullability-completeness
CC 	= gcc
OBJ 	= ./ft_printf.o ./flags_finder.o ./type_ls_treatment.o \
    	  ./flags_treatment_oxx.o ./flags_treatment_diu.o \
    	  ./flags_treatment_s.o ./utilitaries.o \
		  ./flags_treatment_f.o ./utilitaries_4.o \
    	  ./utilitaries_2.o ./utilitaries_3.o ./error_mgmt.o \
		  flags_treatment_percent.o
	CL=\x1b[35m
	GREEN=\033[1;32m
	RED=\033[1;31m
	CL2=\x1b[36m
	NC=\033[0m

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) -c $(FLAGS) $(SRC)
	@ar rcs $(NAME) $(OBJ)
	@rm -rf $(OBJ) 
	@echo "$(GREEN)[✓]$(NC)$(CL) lib $(NAME) built$(NC)"

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)[-]$(NC)$(CL2) Objects of $(NAME) cleaned$(NC)"

fclean: clean
	@rm -rf libftprintf.a
	@echo "$(RED)[-]$(NC)$(CL2) ft_printf cleaned$(NC)"
	@echo "$(RED)[-]$(NC)$(CL2) Library $(NAME) cleaned$(NC)"

re: fclean all

.PHONY: test, all, $(NAME), clean, fclean, re
